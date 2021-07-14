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
#include <pthread.h>



// interface ITask
class ITask {
public:
    virtual ~ITask() = default;
    virtual void run() = 0;
};



class ThreadPoolV2B {

private:
    int numThreads = 0;
    std::vector<pthread_t> lstTh;

    std::queue<ITask*> taskPending;
    pthread_mutex_t mutTaskPending = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t condTaskPending = PTHREAD_COND_INITIALIZER;

    std::list<ITask*> taskRunning;
    pthread_mutex_t mutTaskRunning = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t condTaskRunning = PTHREAD_COND_INITIALIZER;

    volatile bool forceThreadShutdown;


public:
    ThreadPoolV2B() = default;
    ThreadPoolV2B(const ThreadPoolV2B& other) = delete;
    ThreadPoolV2B(const ThreadPoolV2B&& other) = delete;
    void operator=(const ThreadPoolV2B& other) = delete;
    void operator=(const ThreadPoolV2B&& other) = delete;


    void init(int numThreads) {
        shutdown();

        mutTaskPending = PTHREAD_MUTEX_INITIALIZER;
        condTaskPending = PTHREAD_COND_INITIALIZER;

        mutTaskRunning = PTHREAD_MUTEX_INITIALIZER;
        condTaskRunning = PTHREAD_COND_INITIALIZER;

        this->numThreads = numThreads;
        lstTh.resize(numThreads);
        forceThreadShutdown = false;

        for (auto&& th : lstTh) {
            pthread_create(&th, nullptr, threadRoutine, this);
        }
    }


    void submit(ITask* task) {
        pthread_mutex_lock(&mutTaskPending);
        taskPending.push(task);
        pthread_mutex_unlock(&mutTaskPending);

        pthread_cond_signal(&condTaskPending);
    }


    void waitTaskDone() {
        bool done = false;

        for (;;) {
            pthread_mutex_lock(&mutTaskPending);

            if (0 == taskPending.size()) {
                pthread_mutex_lock(&mutTaskRunning);

                while (taskRunning.size() > 0)
                    pthread_cond_wait(&condTaskRunning, &mutTaskRunning);

                pthread_mutex_unlock(&mutTaskRunning);

                done = true;
            }

            pthread_mutex_unlock(&mutTaskPending);

            if (done) {
                break;
            }
        }
    }


    void shutdown() {
        pthread_mutex_lock(&mutTaskPending);

        forceThreadShutdown = true;
        std::queue<ITask*>().swap(taskPending);

        pthread_mutex_unlock(&mutTaskPending);

        pthread_cond_broadcast(&condTaskPending);

        for (auto&& th : lstTh) {
            pthread_join(th, nullptr);
        }

        numThreads = 0;
        lstTh.clear();

        pthread_mutex_destroy(&mutTaskPending);
        pthread_cond_destroy(&condTaskPending);
        pthread_mutex_destroy(&mutTaskRunning);
        pthread_cond_destroy(&condTaskRunning);
    }


private:
    static void* threadRoutine(void* argVoid) {
        auto thisPtr = (ThreadPoolV2B*)argVoid;

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
                pthread_mutex_lock(&mutTaskPending);

                while (0 == taskPending.size() and false == forceThreadShutdown) {
                    pthread_cond_wait(&condTaskPending, &mutTaskPending);
                }

                if (forceThreadShutdown) {
                    pthread_mutex_unlock(&mutTaskPending);
                    break;
                }

                // GET THE TASK FROM THE PENDING QUEUE
                task = taskPending.front();
                taskPending.pop();

                // PUSH IT TO THE RUNNING QUEUE
                pthread_mutex_lock(&mutTaskRunning);
                taskRunning.push_back(task);
                pthread_mutex_unlock(&mutTaskRunning);

                pthread_mutex_unlock(&mutTaskPending);
            }

            // DO THE TASK
            task->run();

            // REMOVE IT FROM THE RUNNING QUEUE
            pthread_mutex_lock(&mutTaskRunning);
            taskRunning.remove(task);
            pthread_mutex_unlock(&mutTaskRunning);

            pthread_cond_signal(&condTaskRunning);
        }

        pthread_exit(nullptr);
        return nullptr;
    }

};



#endif // _MY_THREAD_POOL_V2B_HPP_
