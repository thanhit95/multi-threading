/*
PROBLEM: Find the integer in the range 1 to 100000 that has the largest number of divisors.

This source code file contains the solution using multi threads.

There are 2 phases:
- Phase 1:  Each worker finds result on a specific range.
            This phase uses multiple threads.

- Phase 2:  Based on multiple results from workers, main function get the final result with maximum numDiv.
            This phase use a single thread (main function).
*/

#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <pthread.h>
#include "mytool-hires-clock.hpp"
using namespace std;



struct WorkerArg {
    int start;
    int end;

    explicit WorkerArg(int start = 0, int end = 0): start(start), end(end)
    {
    }
};



struct WorkerResult {
    int value;
    int numDiv;

    explicit WorkerResult(int value = 0, int numDiv = 0): value(value), numDiv(numDiv)
    {
    }
};



void* workerRoutine(void *argVoid) {
    auto arg = (WorkerArg*)argVoid;
    int start = arg->start;
    int end = arg->end;

    int resValue = 0;
    int resNumDiv = 0;

    for (int i = start; i <= end; ++i) {
        int numDiv = 0;

        for (int j = i / 2; j > 0; --j)
            if (i % j == 0)
                ++numDiv;

        if (resNumDiv < numDiv) {
            resNumDiv = numDiv;
            resValue = i;
        }
    }

    auto res = new WorkerResult(resValue, resNumDiv);

    pthread_exit(res);
    return (void*)0;
}



void prepare(
    int rangeStart, int rangeEnd,
    int numThreads,
    vector<pthread_t> &pid,
    vector<shared_ptr<WorkerArg>> &workerArg
) {
    pid.resize(numThreads);
    workerArg.resize(numThreads);

    int rangeBlock = (rangeEnd - rangeStart + 1) / numThreads;
    int rangeA = 0, rangeB = 0;

    for (int i = 0; i < numThreads; ++i) {
        rangeA = rangeB;
        rangeB += rangeBlock;

        if (i == numThreads - 1)
            rangeB = rangeEnd + 1;

        workerArg[i] = make_shared<WorkerArg>(rangeA, rangeB - 1);
    }
}



int main() {
    constexpr int RANGE_START = 1;
    constexpr int RANGE_STOP = 100000;
    constexpr int NUM_THREADS = 8;

    vector<pthread_t> pid;
    vector<shared_ptr<WorkerArg>> workerArg;
    vector<shared_ptr<WorkerResult>> workerRes(NUM_THREADS);
    prepare(RANGE_START, RANGE_STOP, NUM_THREADS, pid, workerArg);

    int ret = 0;


    auto tpStart = mytool::HiResClock::now();


    for (int i = 0; i < NUM_THREADS; ++i) {
        ret = pthread_create(&pid[i], nullptr, workerRoutine, (void*)workerArg[i].get());

        if (ret)
            throw runtime_error("error creating a thread");
    }


    for (int i = 0; i < NUM_THREADS; ++i) {
        WorkerResult *result = nullptr;
        ret = pthread_join(pid[i], (void**)&result);
        workerRes[i].reset(result);
    }


    // for (auto res: workerRes) {
    //     cout << res->value << "  " << res->numDiv << endl;
    // }


    auto comparison = [](shared_ptr<WorkerResult> const &lhs, shared_ptr<WorkerResult> const &rhs) -> bool {
        return lhs->numDiv < rhs->numDiv;
    };
    auto finalRes = *max_element(workerRes.begin(), workerRes.end(), comparison);


    auto timeSpan = mytool::HiResClock::getTimeSpan(tpStart);


    cout << "The integer which has largest number of divisors is " << finalRes->value << endl;
    cout << "The largest number of divisor is " << finalRes->numDiv << endl;
    cout << "Time elapsed = " << timeSpan.count() << endl;

    return 0;
}
