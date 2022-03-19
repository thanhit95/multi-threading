/*
MY EXECUTOR SERVICE

Version 1A: Simple executor service
- Method "waitTaskDone" consumes CPU (due to bad synchronization).
*/



#ifndef _MY_EXEC_SERVICE_V1B_HPP_
#define _MY_EXEC_SERVICE_V1B_HPP_



#include <vector>
#include <queue>
#include <pthread.h>
#include "exer07-exec-service-itask.hpp"



class MyExecServiceV1B {

private:
    int numThreads = 0;
    std::vector<pthread_t> lstTh;

    std::queue<ITask*> taskPending;
    pthread_mutex_t mutTaskPending = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t condTaskPending = PTHREAD_COND_INITIALIZER;

    int counterTaskRunning;
    pthread_mutex_t mutTaskRunning = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t condTaskRunning = PTHREAD_COND_INITIALIZER;

    volatile bool forceThreadShutdown;


public:
    MyExecServiceV1B(int numThreads) {
        init(numThreads);
    }


    MyExecServiceV1B(const MyExecServiceV1B& other) = delete;
    MyExecServiceV1B(const MyExecServiceV1B&& other) = delete;
    void operator=(const MyExecServiceV1B& other) = delete;
    void operator=(const MyExecServiceV1B&& other) = delete;


private:
    void init(int numThreads) {
        // shutdown();

        mutTaskPending = PTHREAD_MUTEX_INITIALIZER;
        condTaskPending = PTHREAD_COND_INITIALIZER;

        mutTaskRunning = PTHREAD_MUTEX_INITIALIZER;
        condTaskRunning = PTHREAD_COND_INITIALIZER;

        this->numThreads = numThreads;
        lstTh.resize(numThreads);
        counterTaskRunning = 0;
        forceThreadShutdown = false;

        for (auto&& th : lstTh) {
            pthread_create(&th, nullptr, &threadWorkerFunc, this);
        }
    }


public:
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

            if (taskPending.empty()) {
                pthread_mutex_lock(&mutTaskRunning);

                while (counterTaskRunning > 0)
                    pthread_cond_wait(&condTaskRunning, &mutTaskRunning);

                // no pending task and no running task
                done = true;

                pthread_mutex_unlock(&mutTaskRunning);
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
    static void* threadWorkerFunc(void* argVoid) {
        auto thisPtr = (MyExecServiceV1B*) argVoid;

        auto&& taskPending = thisPtr->taskPending;
        auto&& mutTaskPending = thisPtr->mutTaskPending;
        auto&& condTaskPending = thisPtr->condTaskPending;

        auto&& counterTaskRunning = thisPtr->counterTaskRunning;
        auto&& mutTaskRunning = thisPtr->mutTaskRunning;
        auto&& condTaskRunning = thisPtr->condTaskRunning;

        auto&& forceThreadShutdown = thisPtr->forceThreadShutdown;


        for (;;) {
            // WAIT FOR AN AVAILABLE PENDING TASK
            pthread_mutex_lock(&mutTaskPending);

            while (taskPending.empty() and false == forceThreadShutdown) {
                pthread_cond_wait(&condTaskPending, &mutTaskPending);
            }

            if (forceThreadShutdown) {
                pthread_mutex_unlock(&mutTaskPending);
                break;
            }

            // GET THE TASK FROM THE PENDING QUEUE
            auto task = taskPending.front();
            taskPending.pop();

            ++counterTaskRunning;

            pthread_mutex_unlock(&mutTaskPending);

            // DO THE TASK
            task->run();

            pthread_mutex_lock(&mutTaskRunning);

            --counterTaskRunning;
            if (0 == counterTaskRunning) {
                pthread_cond_signal(&condTaskRunning);
            }

            pthread_mutex_unlock(&mutTaskRunning);
        }

        pthread_exit(nullptr);
        return nullptr;
    }

};



#endif // _MY_EXEC_SERVICE_V1B_HPP_
