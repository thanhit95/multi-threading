/*
MY EXECUTOR SERVICE

Version 0B: The easiest executor service
- It uses a blocking queue as underlying mechanism.
- It supports waitTaskDone() and shutdown().
*/



#ifndef _MY_EXEC_SERVICE_V0B_HPP_
#define _MY_EXEC_SERVICE_V0B_HPP_



#include <vector>
#include <boost/chrono.hpp>
#include <boost/thread.hpp>
#include "mylib-blockingqueue.hpp"
#include "exer08-exec-service-itask.hpp"



class MyExecServiceV0B {

private:
    int numThreads;
    boost::thread_group lstTh;

    mylib::BlockingQueue<ITask*> taskPending;
    boost::atomic_int32_t counterTaskRunning;

    volatile bool forceThreadShutdown;

    const class : ITask {
        void run() { }
    }
    emptyTask;


public:
    MyExecServiceV0B(int numThreads) {
        init(numThreads);
    }


private:
    MyExecServiceV0B(const MyExecServiceV0B& other) : numThreads(0) { }
    void operator=(const MyExecServiceV0B& other) { }

#if __cplusplus >= 201103L || (defined(_MSC_VER) && _MSC_VER >= 1900)
    MyExecServiceV0B(const MyExecServiceV0B&& other) : numThreads(0) { }
    void operator=(const MyExecServiceV0B&& other) { }
#endif


private:
    void init(int numThreads) {
        this->numThreads = numThreads;
        counterTaskRunning = 0;
        forceThreadShutdown = false;

        for (int i = 0; i < numThreads; ++i) {
            lstTh.add_thread(new boost::thread(&threadWorkerFunc, this));
        }
    }


public:
    void submit(ITask* task) {
        taskPending.add(task);
    }


    void waitTaskDone() {
        // This ExecService is too simple,
        // so there is no good implementation for waitTaskDone()
        while (false == taskPending.empty() || counterTaskRunning > 0) {
            boost::this_thread::sleep_for(boost::chrono::seconds(1));
            // boost::this_thread::yield();
        }
    }


    void shutdown() {
        forceThreadShutdown = true;
        taskPending.clear();

        // Invoke blocked threads by adding "empty" tasks
        for (int i = 0; i < numThreads; ++i) {
            taskPending.put( (ITask* const) &emptyTask );
        }

        lstTh.join_all();
        numThreads = 0;
    }


private:
    static void threadWorkerFunc(MyExecServiceV0B* thisPtr) {
        mylib::BlockingQueue<ITask*> & taskPending = thisPtr->taskPending;
        boost::atomic_int32_t & counterTaskRunning = thisPtr->counterTaskRunning;
        volatile bool & forceThreadShutdown = thisPtr->forceThreadShutdown;

        ITask* task = 0;

        for (;;) {
            // WAIT FOR AN AVAILABLE PENDING TASK
            task = taskPending.take();

            // If shutdown() was called, then exit the function
            if (forceThreadShutdown) {
                break;
            }

            // DO THE TASK
            ++counterTaskRunning;
            task->run();
            --counterTaskRunning;
        }
    }

};



#endif // _MY_EXEC_SERVICE_V0B_HPP_
