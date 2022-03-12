/*
MY EXECUTOR SERVICE

Version 1B: Simple executor service
- Method "waitTaskDone" uses a condition variable to synchronize.
*/



#ifndef _MY_EXEC_SERVICE_V1B_HPP_
#define _MY_EXEC_SERVICE_V1B_HPP_



#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "exer07-exec-service-itask.hpp"



class MyExecServiceV1B {

private:
    using uniquelk = std::unique_lock<std::mutex>;


private:
    int numThreads = 0;
    std::vector<std::thread> lstTh;

    std::queue<ITask*> taskPending;
    std::mutex mutTaskPending;
    std::condition_variable condTaskPending;

    int counterTaskRunning;
    std::mutex mutTaskRunning;
    std::condition_variable condTaskRunning;

    volatile bool forceThreadShutdown;


public:
    MyExecServiceV1B() = default;
    MyExecServiceV1B(const MyExecServiceV1B& other) = delete;
    MyExecServiceV1B(const MyExecServiceV1B&& other) = delete;
    void operator=(const MyExecServiceV1B& other) = delete;
    void operator=(const MyExecServiceV1B&& other) = delete;


    void init(int numThreads) {
        shutdown();

        this->numThreads = numThreads;
        lstTh.resize(numThreads);
        counterTaskRunning = 0;
        forceThreadShutdown = false;

        for (auto&& th : lstTh) {
            th = std::thread(threadWorkerFunc, this);
        }
    }


    void submit(ITask* task) {
        {
            uniquelk lk(mutTaskPending);
            taskPending.push(task);
        }

        condTaskPending.notify_one();
    }


    void waitTaskDone() {
        for (;;) {
            uniquelk lkPending(mutTaskPending);

            if (0 == taskPending.size()) {
                uniquelk lkRunning(mutTaskRunning);

                while (counterTaskRunning > 0)
                    condTaskRunning.wait(lkRunning);

                // no pending task and no running task
                break;
            }
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
    static void threadWorkerFunc(MyExecServiceV1B* thisPtr) {
        auto&& taskPending = thisPtr->taskPending;
        auto&& mutTaskPending = thisPtr->mutTaskPending;
        auto&& condTaskPending = thisPtr->condTaskPending;

        auto&& counterTaskRunning = thisPtr->counterTaskRunning;
        auto&& mutTaskRunning = thisPtr->mutTaskRunning;
        auto&& condTaskRunning = thisPtr->condTaskRunning;

        auto&& forceThreadShutdown = thisPtr->forceThreadShutdown;

        ITask* task = nullptr;


        for (;;) {
            {
                // WAIT FOR AN AVAILABLE PENDING TASK
                uniquelk lkPending(mutTaskPending);

                while (0 == taskPending.size() && false == forceThreadShutdown) {
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

            {
                uniquelk lkRunning(mutTaskRunning);
                --counterTaskRunning;

                if (0 == counterTaskRunning) {
                    condTaskRunning.notify_one();
                }
            }
        }
    }

};



#endif // _MY_EXEC_SERVICE_V1B_HPP_
