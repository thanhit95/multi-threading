/*
MY EXECUTOR SERVICE

Version 1A: Simple executor service
- Method "waitTaskDone" invokes thread sleeps in loop (which can cause performance problems).
*/



#ifndef _MY_EXEC_SERVICE_V1A_HPP_
#define _MY_EXEC_SERVICE_V1A_HPP_



#include <vector>
#include <queue>
#include <chrono>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include "exer08-exec-service-itask.hpp"



class MyExecServiceV1A {

private:
    using uniquelk = std::unique_lock<std::mutex>;


private:
    int numThreads = 0;
    std::vector<std::thread> lstTh;

    std::queue<ITask*> taskPending;
    std::mutex mutTaskPending;
    std::condition_variable condTaskPending;

    std::atomic_int32_t counterTaskRunning;

    volatile bool forceThreadShutdown;


public:
    MyExecServiceV1A(int numThreads) {
        init(numThreads);
    }


    MyExecServiceV1A(const MyExecServiceV1A& other) = delete;
    MyExecServiceV1A(const MyExecServiceV1A&& other) = delete;
    void operator=(const MyExecServiceV1A& other) = delete;
    void operator=(const MyExecServiceV1A&& other) = delete;


private:
    void init(int numThreads) {
        // shutdown();

        this->numThreads = numThreads;
        lstTh.resize(numThreads);
        counterTaskRunning = 0;
        forceThreadShutdown = false;

        for (auto&& th : lstTh) {
            th = std::thread(&threadWorkerFunc, this);
        }
    }


public:
    void submit(ITask* task) {
        {
            uniquelk lk(mutTaskPending);
            taskPending.push(task);
        }

        condTaskPending.notify_one();
    }


    void waitTaskDone() {
        bool done = false;

        for (;;) {
            {
                uniquelk lk(mutTaskPending);

                if (taskPending.empty() && 0 == counterTaskRunning) {
                    done = true;
                }
            }

            if (done) {
                break;
            }

            std::this_thread::sleep_for(std::chrono::seconds(1));
            // std::this_thread::yield();
        }
    }


    void shutdown() {
        {
            uniquelk lk(mutTaskPending);
            forceThreadShutdown = true;
            std::queue<ITask*>().swap(taskPending);
        }

        condTaskPending.notify_all();

        for (auto&& th : lstTh) {
            th.join();
        }

        numThreads = 0;
        lstTh.clear();
    }


private:
    static void threadWorkerFunc(MyExecServiceV1A* thisPtr) {
        auto&& taskPending = thisPtr->taskPending;
        auto&& mutTaskPending = thisPtr->mutTaskPending;
        auto&& condTaskPending = thisPtr->condTaskPending;

        auto&& counterTaskRunning = thisPtr->counterTaskRunning;
        auto&& forceThreadShutdown = thisPtr->forceThreadShutdown;

        ITask* task = nullptr;


        for (;;) {
            {
                // WAIT FOR AN AVAILABLE PENDING TASK
                uniquelk lkPending(mutTaskPending);

                while (taskPending.empty() && false == forceThreadShutdown) {
                    condTaskPending.wait(lkPending);
                }

                if (forceThreadShutdown) {
                    // lkPending.unlock(); // remember this statement
                    break;
                }

                // GET THE TASK FROM THE PENDING QUEUE
                task = taskPending.front();
                taskPending.pop();

                ++counterTaskRunning;
            }

            // DO THE TASK
            task->run();

            --counterTaskRunning;
        }
    }

};



#endif // _MY_EXEC_SERVICE_V1A_HPP_
