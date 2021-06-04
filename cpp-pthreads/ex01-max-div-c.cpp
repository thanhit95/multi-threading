/*
PROBLEM: Find the integer in the range 1 to 100000 that has the largest number of divisors.

This source code file contains the solution using multi threads.

The difference between VERSION C and VERSION B is:
- Each worker finds result on a specific range, and then update final result.
- So, main function does not need to process in order to get final result.
*/

#include <iostream>
#include <memory>
#include <vector>
#include <stdexcept>
#include <pthread.h>
#include "mytool-hires-clock.hpp"
using namespace std;



class FinalResult {
private:
    int value = 0;
    int numDiv = 0;
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

public:
    FinalResult() { }

    void update(int value, int numDiv) {
        pthread_mutex_lock(&mutex);

        if (this->numDiv < numDiv) {
            this->numDiv = numDiv;
            this->value = value;
        }

        pthread_mutex_unlock(&mutex);
    }

    int getValue() const { return value; }
    int getNumDiv() const { return numDiv; }

private:
    FinalResult(const FinalResult &other) = delete;
    FinalResult(const FinalResult &&other) = delete;
    void operator=(const FinalResult &other) = delete;
    void operator=(const FinalResult &&other) = delete;
};



struct WorkerArg {
    int start;
    int end;
    FinalResult *finalRes;

    explicit WorkerArg(int start = 0, int end = 0, FinalResult *finalRes = nullptr):
        start(start), end(end), finalRes(finalRes)
    {
    }
};



void* workerRoutine(void *argVoid) {
    auto arg = (WorkerArg*)argVoid;
    int start = arg->start;
    int end = arg->end;
    FinalResult *finalRes = arg->finalRes;

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

    finalRes->update(resValue, resNumDiv);

    pthread_exit(nullptr);
    return (void*)0;
}



void prepare(
    int rangeStart, int rangeEnd,
    int numThreads,
    vector<pthread_t> &pid,
    vector<shared_ptr<WorkerArg>> &workerArg,
    FinalResult *ptrFinalRes
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

        workerArg[i] = make_shared<WorkerArg>(rangeA, rangeB - 1, ptrFinalRes);
    }
}



int main() {
    constexpr int RANGE_START = 1;
    constexpr int RANGE_STOP = 100000;
    constexpr int NUM_THREADS = 8;

    FinalResult finalResult;

    vector<pthread_t> pid;
    vector<shared_ptr<WorkerArg>> workerArg;
    prepare(RANGE_START, RANGE_STOP, NUM_THREADS, pid, workerArg, &finalResult);

    int ret = 0;


    auto tpStart = mytool::HiResClock::now();


    for (int i = 0; i < NUM_THREADS; ++i) {
        ret = pthread_create(&pid[i], nullptr, workerRoutine, (void*)workerArg[i].get());

        if (ret)
            throw runtime_error("error creating a thread");
    }


    for (int i = 0; i < NUM_THREADS; ++i) {
        ret = pthread_join(pid[i], nullptr);
    }


    // for (auto res: workerRes) {
    //     cout << res->value << "  " << res->numDiv << endl;
    // }


    auto timeSpan = mytool::HiResClock::getTimeSpan(tpStart);


    cout << "The integer which has largest number of divisors is " << finalResult.getValue() << endl;
    cout << "The largest number of divisor is " << finalResult.getNumDiv() << endl;
    cout << "Time elapsed = " << timeSpan.count() << endl;

    return 0;
}
