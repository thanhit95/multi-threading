/*
MY THREAD POOL

Version 2B:
- Better synchronization.
- Method "waitTaskDone":
  + uses a condition variable to synchronize.
  + does not consume CPU (compared to version 1).
*/



#ifndef _MY_THREAD_POOL_V2B_HPP_
#define _MY_THREAD_POOL_V2B_HPP_



#include <vector>
#include <list>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>



// interface ITask
class ITask {
public:
    virtual ~ITask() = default;
    virtual void run() = 0;
};



class ThreadPoolV2B {

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
    ThreadPoolV2B() = default;
    ThreadPoolV2B(const ThreadPoolV2B& other) = delete;
    ThreadPoolV2B(const ThreadPoolV2B&& other) = delete;
    void operator=(const ThreadPoolV2B& other) = delete;
    void operator=(const ThreadPoolV2B&& other) = delete;


    void init(int numThreads) {
        shutdown();

        this->numThreads = numThreads;
        lstTh.resize(numThreads);
        forceThreadShutdown = false;

        for (auto&& th : lstTh) {
            th = std::thread(threadRoutine, this);
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
            {
                std::lock_guard<std::mutex> lkPending(mutTaskPending);

                if (0 == taskPending.size()) {
                    std::unique_lock<std::mutex> lkRunning(mutTaskRunning);

                    while (taskRunning.size() > 0)
                        condTaskRunning.wait(lkRunning);

                    // no pending task and no running task
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
    static void threadRoutine(ThreadPoolV2B* thisPtr) {
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
                std::unique_lock<std::mutex> lkPending(mutTaskPending);

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
                    std::lock_guard<std::mutex> lkRunning(mutTaskRunning);
                    taskRunning.push_back(task);
                }
            }

            // DO THE TASK
            task->run();

            // REMOVE IT FROM THE RUNNING QUEUE
            {
                std::lock_guard<std::mutex> lkRunning(mutTaskRunning);
                taskRunning.remove(task);
                condTaskRunning.notify_one();
            }
        }
    }

};



#endif // _MY_THREAD_POOL_V2B_HPP_
