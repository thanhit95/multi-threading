/*
MY THREAD POOL

Version 1:
- Simple thread pool.
- Method "waitTaskDone" consumes CPU (due to bad synchronization).
*/



#ifndef _MY_THREAD_POOL_V1_HPP_
#define _MY_THREAD_POOL_V1_HPP_



#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include "exer07-thread-pool-itask.hpp"



class ThreadPoolV1 {

private:
    int numThreads = 0;
    std::vector<std::thread> lstTh;

    std::queue<ITask*> taskPending;
    std::mutex mutTaskPending;
    std::condition_variable condTaskPending;

    std::atomic_int32_t counterTaskRunning;

    volatile bool forceThreadShutdown;


public:
    ThreadPoolV1() = default;
    ThreadPoolV1(const ThreadPoolV1& other) = delete;
    ThreadPoolV1(const ThreadPoolV1&& other) = delete;
    void operator=(const ThreadPoolV1& other) = delete;
    void operator=(const ThreadPoolV1&& other) = delete;


    void init(int numThreads) {
        shutdown();

        this->numThreads = numThreads;
        lstTh.resize(numThreads);
        counterTaskRunning.store(0);
        forceThreadShutdown = false;

        for (auto&& th : lstTh) {
            th = std::thread(threadWorkerFunc, this);
        }
    }


    void submit(ITask* task) {
        mutTaskPending.lock();
        taskPending.push(task);
        mutTaskPending.unlock();

        condTaskPending.notify_one();
    }


    void waitTaskDone() {
        bool done = false;

        for (;;) {
            mutTaskPending.lock();

            if (0 == taskPending.size() && 0 == counterTaskRunning.load()) {
                done = true;
            }

            mutTaskPending.unlock();

            if (done) {
                break;
            }

            std::this_thread::yield();
        }
    }


    void shutdown() {
        mutTaskPending.lock();

        forceThreadShutdown = true;
        std::queue<ITask*>().swap(taskPending);

        mutTaskPending.unlock();

        condTaskPending.notify_all();

        for (auto&& th : lstTh) {
            th.join();
        }

        numThreads = 0;
        lstTh.clear();
    }


private:
    static void threadWorkerFunc(ThreadPoolV1* thisPtr) {
        auto&& taskPending = thisPtr->taskPending;
        auto&& mutTaskPending = thisPtr->mutTaskPending;
        auto&& condTaskPending = thisPtr->condTaskPending;

        auto&& counterTaskRunning = thisPtr->counterTaskRunning;
        auto&& forceThreadShutdown = thisPtr->forceThreadShutdown;


        for (;;) {
            // WAIT FOR AN AVAILABLE PENDING TASK
            std::unique_lock<std::mutex> lkPending(mutTaskPending);

            while (0 == taskPending.size() && false == forceThreadShutdown) {
                condTaskPending.wait(lkPending);
            }

            if (forceThreadShutdown) {
                // lkPending.unlock(); // remember this statement
                break;
            }


            // GET THE TASK FROM THE PENDING QUEUE
            auto task = taskPending.front();
            taskPending.pop();


            ++counterTaskRunning;


            lkPending.unlock();


            // DO THE TASK
            task->run();
            --counterTaskRunning;
        }
    }

};



#endif // _MY_THREAD_POOL_V1_HPP_
