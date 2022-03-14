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



struct WorkerResult {
    int value;
    int numDiv;

    WorkerResult(int value = 0, int numDiv = 0): value(value), numDiv(numDiv)
    {
    }
};



void workerFunc(WorkerArg* arg, WorkerResult* res) {
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

    (*res) = WorkerResult(resValue, resNumDiv);
}



void prepare(
    int rangeStart, int rangeEnd,
    int numThreads,
    vector<WorkerArg>& lstWorkerArg,
    vector<WorkerResult>& lstWorkerRes
) {
    lstWorkerArg.resize(numThreads);
    lstWorkerRes.resize(numThreads);

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
    vector<WorkerResult> lstWorkerRes;

    prepare(RANGE_START, RANGE_END, NUM_THREADS, lstWorkerArg, lstWorkerRes);

    time_point tpStart = hrclock::now();


    for (int i = 0; i < NUM_THREADS; ++i) {
        lstTh.add_thread(new boost::thread(workerFunc, &lstWorkerArg[i], &lstWorkerRes[i]));
    }

    lstTh.join_all();


    WorkerResult finalRes = lstWorkerRes[0];

    for (int i = 1; i < lstWorkerRes.size(); ++i) {
        if (finalRes.numDiv < lstWorkerRes[i].numDiv) {
            finalRes = lstWorkerRes[i];
        }
    }


    chrmicro timeElapsed = hrclock::getTimeSpan<chrmicro>(tpStart);

    cout << "The integer which has largest number of divisors is " << finalRes.value << endl;
    cout << "The largest number of divisor is " << finalRes.numDiv << endl;
    cout << "Time elapsed = " << (timeElapsed.count() / 1000000.0) << endl;

    return 0;
}
