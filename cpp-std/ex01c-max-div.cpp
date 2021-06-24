#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
#include <mutex>
#include "mytool-time.hpp"
using namespace std;



struct WorkerArg {
    int iStart;
    int iEnd;

    WorkerArg(int iStart = 0, int iEnd = 0): iStart(iStart), iEnd(iEnd)
    {
    }
};



class FinalResult {
public:
    int value = 0;
    int numDiv = 0;

private:
    std::mutex mut;


public:
    void update(int value, int numDiv) {
        mut.lock();

        if (this->numDiv < numDiv) {
            this->numDiv = numDiv;
            this->value = value;
        }

        mut.unlock();
    }
};



void workerRoutine(WorkerArg* arg, FinalResult* res) {
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
    vector<std::thread>& lstTh,
    vector<WorkerArg>& lstWorkerArg
) {
    lstTh.resize(numThreads);
    lstWorkerArg.resize(numThreads);

    int rangeBlock = (rangeEnd - rangeStart + 1) / numThreads;
    int rangeA = 0, rangeB = 0;

    for (int i = 0; i < numThreads; ++i) {
        rangeA = rangeB;
        rangeB += rangeBlock;

        if (i == numThreads - 1)
            rangeB = rangeEnd + 1;

        lstWorkerArg[i] = WorkerArg(rangeA, rangeB - 1);
    }
}



int main() {
    constexpr int RANGE_START = 1;
    constexpr int RANGE_STOP = 100000;
    constexpr int NUM_THREADS = 8;

    vector<std::thread> lstTh;
    vector<WorkerArg> lstWorkerArg;

    FinalResult finalRes;


    prepare(RANGE_START, RANGE_STOP, NUM_THREADS, lstTh, lstWorkerArg);


    auto tpStart = mytool::HiResClock::now();


    for (int i = 0; i < NUM_THREADS; ++i) {
        lstTh[i] = std::thread(workerRoutine, &lstWorkerArg[i], &finalRes);
    }

    for (auto&& th : lstTh) {
        th.join();
    }


    auto timeSpan = mytool::HiResClock::getTimeSpan(tpStart);


    cout << "The integer which has largest number of divisors is " << finalRes.value << endl;
    cout << "The largest number of divisor is " << finalRes.numDiv << endl;
    cout << "Time elapsed = " << timeSpan.count() << endl;

    return 0;
}
