/*
MY EXECUTOR SERVICE

Version 2A: The executor service storing running tasks
- Method "waitTaskDone" uses a semaphore to synchronize.
*/



#ifndef _MY_EXEC_SERVICE_V2A_HPP_
#define _MY_EXEC_SERVICE_V2A_HPP_



#include <vector>
#include <list>
#include <queue>
#include <pthread.h>
#include <semaphore.h>
#include "exer07-exec-service-itask.hpp"



class MyExecServiceV2A {

private:
    int numThreads = 0;
    std::vector<pthread_t> lstTh;

    std::queue<ITask*> taskPending;
    pthread_mutex_t mutTaskPending = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t condTaskPending = PTHREAD_COND_INITIALIZER;

    std::list<ITask*> taskRunning;
    pthread_mutex_t mutTaskRunning = PTHREAD_MUTEX_INITIALIZER;
    sem_t counterTaskRunning;

    volatile bool forceThreadShutdown;


public:
    MyExecServiceV2A() = default;
    MyExecServiceV2A(const MyExecServiceV2A& other) = delete;
    MyExecServiceV2A(const MyExecServiceV2A&& other) = delete;
    void operator=(const MyExecServiceV2A& other) = delete;
    void operator=(const MyExecServiceV2A&& other) = delete;


    void init(int numThreads) {
        shutdown();

        mutTaskPending = PTHREAD_MUTEX_INITIALIZER;
        condTaskPending = PTHREAD_COND_INITIALIZER;

        mutTaskRunning = PTHREAD_MUTEX_INITIALIZER;
        sem_init(&counterTaskRunning, 0, 0);

        this->numThreads = numThreads;
        lstTh.resize(numThreads);
        forceThreadShutdown = false;

        for (auto&& th : lstTh) {
            pthread_create(&th, nullptr, threadWorkerFunc, this);
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
            sem_wait(&counterTaskRunning);

            pthread_mutex_lock(&mutTaskPending);
            pthread_mutex_lock(&mutTaskRunning);

            if (0 == taskPending.size() && 0 == taskRunning.size()) {
                done = true;
            }

            pthread_mutex_unlock(&mutTaskRunning);
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
        sem_destroy(&counterTaskRunning);
    }


private:
    static void* threadWorkerFunc(void* argVoid) {
        auto thisPtr = (MyExecServiceV2A*) argVoid;

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

            sem_post(&counterTaskRunning);
        }

        pthread_exit(nullptr);
        return nullptr;
    }

};



#endif // _MY_EXEC_SERVICE_V2A_HPP_
