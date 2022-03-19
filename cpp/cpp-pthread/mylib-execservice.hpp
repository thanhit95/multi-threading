/******************************************************
*
* File name:    mylib-execservice.hpp
*
* Author:       Name:   Thanh Nguyen
*               Email:  thanh.it1995(at)gmail(dot)com
*
* License:      3-Clause BSD License
*
* Description:  The executor service implementation in C++11 POSIX threading
*
******************************************************/



/*
Copy code from "MyExecServiceV1B"
*/


#ifndef _MYLIB_EXEC_SERVICE_HPP_
#define _MYLIB_EXEC_SERVICE_HPP_



#include <vector>
#include <queue>
#include <functional>
#include <pthread.h>



namespace mylib {



class ExecService {

public:
    using taskFunc = std::function<void()>;


private:
    int numThreads = 0;
    std::vector<pthread_t> lstTh;

    std::queue<taskFunc> taskPending;
    pthread_mutex_t mutTaskPending = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t condTaskPending = PTHREAD_COND_INITIALIZER;

    int counterTaskRunning;
    pthread_mutex_t mutTaskRunning = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t condTaskRunning = PTHREAD_COND_INITIALIZER;

    volatile bool forceThreadShutdown;


public:
    ExecService(int numThreads) {
        init(numThreads);
    }


    ExecService(const ExecService& other) = delete;
    ExecService(const ExecService&& other) = delete;
    void operator=(const ExecService& other) = delete;
    void operator=(const ExecService&& other) = delete;


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
    void submit(taskFunc task) {
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
        std::queue<taskFunc>().swap(taskPending);

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
        auto thisPtr = (ExecService*) argVoid;

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
            task();

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

}; // ExecService



} // namespace mylib



#endif // _MYLIB_EXEC_SERVICE_HPP_
