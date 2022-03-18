/*
MAXIMUM NUMBER OF DIVISORS
*/


#include <iostream>
#include <vector>
#include <algorithm>
#include <boost/thread.hpp>
#include "mylib-time.hpp"
using namespace std;



typedef boost::chrono::microseconds chrmicro;
typedef boost::chrono::steady_clock::time_point time_point;
typedef mylib::HiResClock hrclock;



struct WorkerArg {
    int iStart;
    int iEnd;

    WorkerArg(int iStart = 0, int iEnd = 0): iStart(iStart), iEnd(iEnd)
    {
    }
};



class FinalResult {
public:
    int value;
    int numDiv;

private:
    boost::mutex mut;


public:
    FinalResult(): value(0), numDiv(0) { }


    void update(int value, int numDiv) {
        // Synchronize whole function
        boost::unique_lock<boost::mutex> lk(mut);

        if (this->numDiv < numDiv) {
            this->numDiv = numDiv;
            this->value = value;
        }
    }
};



void workerFunc(WorkerArg* arg, FinalResult* res) {
    int resValue = 0;
    int resNumDiv = 0;

    for (int i = arg->iStart; i <= arg->iEnd; ++i) {
        int numDiv = 0;

        for (int j = i / 2; j > 0; --j)
            if (i % j == 0)
                ++numDiv;

        if (resNumDiv < numDiv) {
            resNumDiv = numDiv;
            resValue = i;
        }
    }

    res->update(resValue, resNumDiv);
}



void prepare(
    int rangeStart, int rangeEnd,
    int numThreads,
    vector<WorkerArg>& lstWorkerArg
) {
    lstWorkerArg.resize(numThreads);

    int rangeA, rangeB, rangeBlock;

    rangeBlock = (rangeEnd - rangeStart + 1) / numThreads;
    rangeA = rangeStart;

    for (int i = 0; i < numThreads; ++i, rangeA += rangeBlock) {
        rangeB = rangeA + rangeBlock - 1;

        if (i == numThreads - 1)
            rangeB = rangeEnd;

        lstWorkerArg[i] = WorkerArg(rangeA, rangeB);
    }
}



int main() {
    const int RANGE_START = 1;
    const int RANGE_END = 100000;
    const int NUM_THREADS = 8;

    boost::thread_group lstTh;
    vector<WorkerArg> lstWorkerArg;

    FinalResult finalRes;

    prepare(RANGE_START, RANGE_END, NUM_THREADS, lstWorkerArg);

    time_point tpStart = hrclock::now();


    for (int i = 0; i < NUM_THREADS; ++i) {
        lstTh.add_thread(new boost::thread(&workerFunc, &lstWorkerArg[i], &finalRes));
    }

    lstTh.join_all();


    chrmicro timeElapsed = hrclock::getTimeSpan<chrmicro>(tpStart);

    cout << "The integer which has largest number of divisors is " << finalRes.value << endl;
    cout << "The largest number of divisor is " << finalRes.numDiv << endl;
    cout << "Time elapsed = " << (timeElapsed.count() / 1000000.0) << endl;

    return 0;
}
