/*
MY EXECUTOR SERVICE

Version 1A: Simple executor service
- Method "waitTaskDone" invokes thread sleeps in loop (which can cause performance problems).
*/



#ifndef _MY_EXEC_SERVICE_V1A_HPP_
#define _MY_EXEC_SERVICE_V1A_HPP_



#include <vector>
#include <queue>
#include <boost/chrono.hpp>
#include <boost/thread.hpp>
#include "exer07-exec-service-itask.hpp"



class MyExecServiceV1A {

private:
    typedef boost::unique_lock<boost::mutex> uniquelk;


private:
    int numThreads;
    boost::thread_group lstTh;

    std::queue<ITask*> taskPending;
    boost::mutex mutTaskPending;
    boost::condition_variable condTaskPending;

    boost::atomic_int32_t counterTaskRunning;

    volatile bool forceThreadShutdown;


public:
    MyExecServiceV1A(int numThreads) {
        init(numThreads);
    }


private:
    MyExecServiceV1A(const MyExecServiceV1A& other) : numThreads(0) { }
    void operator=(const MyExecServiceV1A& other) { }

#if __cplusplus >= 201103L || (defined(_MSC_VER) && _MSC_VER >= 1900)
    MyExecServiceV1A(const MyExecServiceV1A&& other) : numThreads(0) { }
    void operator=(const MyExecServiceV1A&& other) { }
#endif


private:
    void init(int numThreads) {
        // shutdown();

        this->numThreads = numThreads;
        counterTaskRunning.store(0);
        forceThreadShutdown = false;

        for (int i = 0; i < numThreads; ++i) {
            lstTh.add_thread(new boost::thread(&threadWorkerFunc, this));
        }
    }


public:
    void submit(ITask* task) {
        {
            uniquelk lk(mutTaskPending);
            taskPending.push(task);
        }

        condTaskPending.notify_one();
    }


    void waitTaskDone() {
        bool done = false;

        for (;;) {
            {
                uniquelk lk(mutTaskPending);

                if (0 == taskPending.size() && 0 == counterTaskRunning.load()) {
                    done = true;
                }
            }

            if (done) {
                break;
            }

            boost::this_thread::sleep_for(boost::chrono::seconds(1));
            // boost::this_thread::yield();
        }
    }


    void shutdown() {
        {
            uniquelk lk(mutTaskPending);
            forceThreadShutdown = true;

            while (false == taskPending.empty())
                taskPending.pop();
        }

        condTaskPending.notify_all();
        lstTh.join_all();
        numThreads = 0;
    }


private:
    static void threadWorkerFunc(MyExecServiceV1A* thisPtr) {
        std::queue<ITask*> & taskPending = thisPtr->taskPending;
        boost::mutex & mutTaskPending = thisPtr->mutTaskPending;
        boost::condition_variable & condTaskPending = thisPtr->condTaskPending;

        boost::atomic_int32_t & counterTaskRunning = thisPtr->counterTaskRunning;
        volatile bool & forceThreadShutdown = thisPtr->forceThreadShutdown;

        ITask* task = 0;


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

                ++counterTaskRunning;
            }

            // DO THE TASK
            task->run();

            --counterTaskRunning;
        }
    }

};



#endif // _MY_EXEC_SERVICE_V1A_HPP_
