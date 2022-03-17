/*
MY EXECUTOR SERVICE

Version 0A: The easiest executor service
- It uses a blocking queue as underlying mechanism.
*/



#ifndef _MY_EXEC_SERVICE_V0A_HPP_
#define _MY_EXEC_SERVICE_V0A_HPP_



#include <iostream>
#include <vector>
#include <unistd.h>
#include <pthread.h>
#include "mylib-blockingqueue.hpp"
#include "exer07-exec-service-itask.hpp"



class MyExecServiceV0A {

private:
    int numThreads = 0;
    std::vector<pthread_t> lstTh;
    mylib::BlockingQueue<ITask*> taskPending;


public:
    MyExecServiceV0A(int numThreads) {
        init(numThreads);
    }


    MyExecServiceV0A(const MyExecServiceV0A& other) = delete;
    MyExecServiceV0A(const MyExecServiceV0A&& other) = delete;
    void operator=(const MyExecServiceV0A& other) = delete;
    void operator=(const MyExecServiceV0A&& other) = delete;


private:
    void init(int numThreads) {
        this->numThreads = numThreads;
        lstTh.resize(numThreads);

        for (auto&& th : lstTh) {
            pthread_create(&th, nullptr, threadWorkerFunc, this);
        }
    }


public:
    void submit(ITask* task) {
        taskPending.add(task);
    }


    void waitTaskDone() {
        // This ExecService is too simple,
        // so there is no implementation for waitTaskDone()
        sleep(11); // fake behaviour
    }


    void shutdown() {
        // This ExecService is too simple,
        // so there is no implementation for shutdown()
        std::cout << "No implementation for shutdown()." << std::endl;
        std::cout << "You need to exit the app manually." << std::endl;
    }


private:
    static void* threadWorkerFunc(void* argVoid) {
        auto thisPtr = (MyExecServiceV0A*) argVoid;
        auto&& taskPending = thisPtr->taskPending;

        for (;;) {
            // WAIT FOR AN AVAILABLE PENDING TASK
            auto task = taskPending.take();

            // DO THE TASK
            task->run();
        }

        pthread_exit(nullptr);
        return nullptr;
    }

};



#endif // _MY_EXEC_SERVICE_V0A_HPP_
