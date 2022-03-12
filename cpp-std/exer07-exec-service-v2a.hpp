/*
MY EXECUTOR SERVICE

Version 2A:
- Better synchronization.
- Method "waitTaskDone":
  + uses a semaphore to synchronize.
  + does not consume CPU (compared to version 1).
*/



#ifndef _MY_EXEC_SERVICE_V2A_HPP_
#define _MY_EXEC_SERVICE_V2A_HPP_



#include <vector>
#include <list>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <semaphore>
#include "exer07-exec-service-itask.hpp"



class MyExecServiceV2A {

private:
    using cntsemaphore = std::counting_semaphore<>;
    using uniquelk = std::unique_lock<std::mutex>;


private:
    int numThreads = 0;
    std::vector<std::thread> lstTh;

    std::queue<ITask*> taskPending;
    std::mutex mutTaskPending;
    std::condition_variable condTaskPending;

    std::list<ITask*> taskRunning;
    std::mutex mutTaskRunning;
    cntsemaphore counterTaskRunning = cntsemaphore(0);

    volatile bool forceThreadShutdown;


public:
    MyExecServiceV2A() = default;
    MyExecServiceV2A(const MyExecServiceV2A& other) = delete;
    MyExecServiceV2A(const MyExecServiceV2A&& other) = delete;
    void operator=(const MyExecServiceV2A& other) = delete;
    void operator=(const MyExecServiceV2A&& other) = delete;


    void init(int numThreads) {
        shutdown();

        this->numThreads = numThreads;
        lstTh.resize(numThreads);
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
        for (;;) {
            counterTaskRunning.acquire();

            {
                uniquelk lkPending(mutTaskPending);
                uniquelk lkRunning(mutTaskRunning);

                if (0 == taskPending.size() && 0 == taskRunning.size()) {
                    break;
                }
            }
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
    static void threadWorkerFunc(MyExecServiceV2A* thisPtr) {
        auto&& taskPending = thisPtr->taskPending;
        auto&& mutTaskPending = thisPtr->mutTaskPending;
        auto&& condTaskPending = thisPtr->condTaskPending;

        auto&& taskRunning = thisPtr->taskRunning;
        auto&& mutTaskRunning = thisPtr->mutTaskRunning;
        auto&& counterTaskRunning = thisPtr->counterTaskRunning;

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

                // PUSH IT TO THE RUNNING QUEUE
                {
                    uniquelk lkRunning(mutTaskRunning);
                    taskRunning.push_back(task);
                }
            }

            // DO THE TASK
            task->run();

            // REMOVE IT FROM THE RUNNING QUEUE
            {
                uniquelk lkRunning(mutTaskRunning);
                taskRunning.remove(task);
                counterTaskRunning.release();
            }
        }
    }

};



#endif // _MY_EXEC_SERVICE_V2A_HPP_
