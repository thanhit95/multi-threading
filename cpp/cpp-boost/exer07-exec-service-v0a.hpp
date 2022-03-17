/*
MY EXECUTOR SERVICE

Version 0A: The easiest executor service
- It uses a blocking queue as underlying mechanism.
*/



#ifndef _MY_EXEC_SERVICE_V0A_HPP_
#define _MY_EXEC_SERVICE_V0A_HPP_



#include <iostream>
#include <vector>
#include <boost/chrono.hpp>
#include <boost/thread.hpp>
#include "mylib-blockingqueue.hpp"
#include "exer07-exec-service-itask.hpp"



class MyExecServiceV0A {

private:
    int numThreads;
    boost::thread_group lstTh;
    mylib::BlockingQueue<ITask*> taskPending;


public:
    MyExecServiceV0A(int numThreads) {
        init(numThreads);
    }


private:
    MyExecServiceV0A(const MyExecServiceV0A& other) : numThreads(0) { }
    void operator=(const MyExecServiceV0A& other) { }

#if __cplusplus >= 201103L || (defined(_MSC_VER) && _MSC_VER >= 1900)
    MyExecServiceV0A(const MyExecServiceV0A&& other) : numThreads(0) { }
    void operator=(const MyExecServiceV0A&& other) { }
#endif


private:
    void init(int numThreads) {
        this->numThreads = numThreads;

        for (int i = 0; i < numThreads; ++i) {
            lstTh.add_thread(new boost::thread(threadWorkerFunc, this));
        }
    }


public:
    void submit(ITask* task) {
        taskPending.add(task);
    }


    void waitTaskDone() {
        // This ExecService is too simple,
        // so there is no implementation for waitTaskDone()
        boost::this_thread::sleep_for(boost::chrono::seconds(11)); // fake behaviour
    }


    void shutdown() {
        // This ExecService is too simple,
        // so there is no implementation for shutdown()
        std::cout << "No implementation for shutdown()." << std::endl;
        std::cout << "You need to exit the app manually." << std::endl;
        lstTh.join_all();
    }


private:
    static void threadWorkerFunc(MyExecServiceV0A* thisPtr) {
        mylib::BlockingQueue<ITask*> & taskPending = thisPtr->taskPending;
        ITask* task = 0;

        for (;;) {
            // WAIT FOR AN AVAILABLE PENDING TASK
            task = taskPending.take();

            // DO THE TASK
            task->run();
        }
    }

};



#endif // _MY_EXEC_SERVICE_V0A_HPP_
