#include <iostream>
#include <vector>
#include <algorithm>
#include <pthread.h>
#include "mytool-time.hpp"
using namespace std;



struct WorkerResult {
    int value;
    int numDiv;

    WorkerResult(int value = 0, int numDiv = 0): value(value), numDiv(numDiv)
    {
    }
};



struct WorkerArg {
    int iStart;
    int iEnd;
    WorkerResult *res;

    WorkerArg(int iStart = 0, int iEnd = 0, WorkerResult *res = nullptr):
        iStart(iStart), iEnd(iEnd), res(res)
    {
    }
};



void* workerRoutine(void* argVoid) {
    auto arg = (WorkerArg*)argVoid;
    auto res = arg->res;

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

    pthread_exit(nullptr);
    return nullptr;
}



void prepare(
    int rangeStart, int rangeEnd,
    int numThreads,
    vector<pthread_t>& lstTid,
    vector<WorkerArg>& lstWorkerArg,
    vector<WorkerResult>& lstWorkerRes
) {
    lstTid.resize(numThreads);
    lstWorkerArg.resize(numThreads);
    lstWorkerRes.resize(numThreads);

    int rangeBlock = (rangeEnd - rangeStart + 1) / numThreads;
    int rangeA = 0, rangeB = 0;

    for (int i = 0; i < numThreads; ++i) {
        rangeA = rangeB;
        rangeB += rangeBlock;

        if (i == numThreads - 1)
            rangeB = rangeEnd + 1;

        lstWorkerArg[i] = WorkerArg(rangeA, rangeB - 1, &lstWorkerRes[i]);
    }
}



int main() {
    constexpr int RANGE_START = 1;
    constexpr int RANGE_STOP = 100000;
    constexpr int NUM_THREADS = 8;

    vector<pthread_t> lstTid;
    vector<WorkerArg> lstWorkerArg;
    vector<WorkerResult> lstWorkerRes;

    int ret = 0;


    prepare(RANGE_START, RANGE_STOP, NUM_THREADS, lstTid, lstWorkerArg, lstWorkerRes);


    auto tpStart = mytool::HiResClock::now();


    for (int i = 0; i < NUM_THREADS; ++i) {
        ret = pthread_create(&lstTid[i], nullptr, workerRoutine, &lstWorkerArg[i]);
    }

    for (auto&& tid : lstTid) {
        ret = pthread_join(tid, nullptr);
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
