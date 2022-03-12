/*
MY EXECUTOR SERVICE

Version 2B:
- Better synchronization.
- Method "waitTaskDone":
  + uses a condition variable to synchronize.
  + does not consume CPU (compared to version 1).
*/



#ifndef _MY_EXEC_SERVICE_V2B_HPP_
#define _MY_EXEC_SERVICE_V2B_HPP_



#include <vector>
#include <list>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "exer07-exec-service-itask.hpp"



class MyExecServiceV2B {

private:
    using uniquelk = std::unique_lock<std::mutex>;


private:
    int numThreads = 0;
    std::vector<std::thread> lstTh;

    std::queue<ITask*> taskPending;
    std::mutex mutTaskPending;
    std::condition_variable condTaskPending;

    std::list<ITask*> taskRunning;
    std::mutex mutTaskRunning;
    std::condition_variable condTaskRunning;

    volatile bool forceThreadShutdown;


public:
    MyExecServiceV2B() = default;
    MyExecServiceV2B(const MyExecServiceV2B& other) = delete;
    MyExecServiceV2B(const MyExecServiceV2B&& other) = delete;
    void operator=(const MyExecServiceV2B& other) = delete;
    void operator=(const MyExecServiceV2B&& other) = delete;


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

                while (taskRunning.size() > 0)
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
    static void threadWorkerFunc(MyExecServiceV2B* thisPtr) {
        auto&& taskPending = thisPtr->taskPending;
        auto&& mutTaskPending = thisPtr->mutTaskPending;
        auto&& condTaskPending = thisPtr->condTaskPending;

        auto&& taskRunning = thisPtr->taskRunning;
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
                condTaskRunning.notify_one();
            }
        }
    }

};



#endif // _MY_EXEC_SERVICE_V2B_HPP_
