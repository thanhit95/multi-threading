/*
MAXIMUM NUMBER OF DIVISORS
*/


#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
#include "mytool-time.hpp"
using namespace std;



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
    vector<std::thread>& lstTh,
    vector<WorkerArg>& lstWorkerArg,
    vector<WorkerResult>& lstWorkerRes
) {
    lstTh.resize(numThreads);
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
    constexpr int RANGE_START = 1;
    constexpr int RANGE_STOP = 100000;
    constexpr int NUM_THREADS = 8;

    vector<std::thread> lstTh;
    vector<WorkerArg> lstWorkerArg;
    vector<WorkerResult> lstWorkerRes;


    prepare(RANGE_START, RANGE_STOP, NUM_THREADS, lstTh, lstWorkerArg, lstWorkerRes);


    auto tpStart = mytool::HiResClock::now();


    for (int i = 0; i < NUM_THREADS; ++i) {
        lstTh[i] = std::thread(workerFunc, &lstWorkerArg[i], &lstWorkerRes[i]);
    }

    for (auto&& th : lstTh) {
        th.join();
    }


    // for (auto&& res: lstWorkerRes) {
    //     cout << res.value << "  " << res.numDiv << endl;
    // }


    auto finalRes = *max_element(lstWorkerRes.begin(), lstWorkerRes.end(),
        [](const WorkerResult &lhs, const WorkerResult &rhs) -> bool {
            return lhs.numDiv < rhs.numDiv;
        }
    );


    auto timeElapsed = mytool::HiResClock::getTimeSpan(tpStart);


    cout << "The integer which has largest number of divisors is " << finalRes.value << endl;
    cout << "The largest number of divisor is " << finalRes.numDiv << endl;
    cout << "Time elapsed = " << timeElapsed.count() << endl;

    return 0;
}
