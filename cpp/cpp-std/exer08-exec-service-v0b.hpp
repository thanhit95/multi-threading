/*
MY EXECUTOR SERVICE

Version 0B: The easiest executor service
- It uses a blocking queue as underlying mechanism.
- It supports waitTaskDone() and shutdown().
*/



#ifndef _MY_EXEC_SERVICE_V0B_HPP_
#define _MY_EXEC_SERVICE_V0B_HPP_



#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <atomic>
#include "mylib-blockingqueue.hpp"
#include "exer08-exec-service-itask.hpp"



class MyExecServiceV0B {

private:
    int numThreads = 0;
    std::vector<std::thread> lstTh;

    mylib::BlockingQueue<ITask*> taskPending;
    std::atomic_int32_t counterTaskRunning;

    volatile bool forceThreadShutdown;

    const class : ITask {
        void run() override { }
    }
    emptyTask;


public:
    MyExecServiceV0B(int numThreads) {
        init(numThreads);
    }


    MyExecServiceV0B(const MyExecServiceV0B& other) = delete;
    MyExecServiceV0B(const MyExecServiceV0B&& other) = delete;
    void operator=(const MyExecServiceV0B& other) = delete;
    void operator=(const MyExecServiceV0B&& other) = delete;


private:
    void init(int numThreads) {
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
        taskPending.add(task);
    }


    void waitTaskDone() {
        // This ExecService is too simple,
        // so there is no good implementation for waitTaskDone()
        while (false == taskPending.empty() || counterTaskRunning > 0) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            // std::this_thread::yield();
        }
    }


    void shutdown() {
        forceThreadShutdown = true;
        taskPending.clear();

        // Invoke blocked threads by adding "empty" tasks
        for (int i = 0; i < numThreads; ++i) {
            taskPending.put( (ITask* const) &emptyTask );
        }

        for (auto&& th : lstTh) {
            th.join();
        }

        numThreads = 0;
        lstTh.clear();
    }


private:
    static void threadWorkerFunc(MyExecServiceV0B* thisPtr) {
        auto&& taskPending = thisPtr->taskPending;
        auto&& counterTaskRunning = thisPtr->counterTaskRunning;
        auto&& forceThreadShutdown = thisPtr->forceThreadShutdown;

        ITask* task = nullptr;

        for (;;) {
            // WAIT FOR AN AVAILABLE PENDING TASK
            task = taskPending.take();

            // If shutdown() was called, then exit the function
            if (forceThreadShutdown) {
                break;
            }

            // DO THE TASK
            ++counterTaskRunning;
            task->run();
            --counterTaskRunning;
        }
    }

};



#endif // _MY_EXEC_SERVICE_V0B_HPP_
