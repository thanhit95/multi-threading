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
#include <boost/thread.hpp>
#include "mylib-semaphore.hpp"
#include "exer07-exec-service-itask.hpp"



class MyExecServiceV2A {

private:
    typedef boost::unique_lock<boost::mutex> uniquelk;


private:
    int numThreads;
    boost::thread_group lstTh;

    std::queue<ITask*> taskPending;
    boost::mutex mutTaskPending;
    boost::condition_variable condTaskPending;

    std::list<ITask*> taskRunning;
    boost::mutex mutTaskRunning;
    mylib::Semaphore counterTaskRunning;

    volatile bool forceThreadShutdown;


public:
    MyExecServiceV2A(int numThreads) : counterTaskRunning(0) {
        init(numThreads);
    }


private:
    MyExecServiceV2A(const MyExecServiceV2A& other) : numThreads(0), counterTaskRunning(0) { }
    void operator=(const MyExecServiceV2A& other) { }

#if __cplusplus >= 201103L || (defined(_MSC_VER) && _MSC_VER >= 1900)
    MyExecServiceV2A(const MyExecServiceV2A&& other) : numThreads(0), counterTaskRunning(0) { }
    void operator=(const MyExecServiceV2A&& other) { }
#endif


private:
    void init(int numThreads) {
        // shutdown();

        this->numThreads = numThreads;
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
        for (;;) {
            counterTaskRunning.acquire();

            {
                uniquelk lkPending(mutTaskPending);
                uniquelk lkRunning(mutTaskRunning);

                if (taskPending.empty() && taskRunning.empty()) {
                    break;
                }
            }
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
    static void threadWorkerFunc(MyExecServiceV2A* thisPtr) {
        std::queue<ITask*> & taskPending = thisPtr->taskPending;
        boost::mutex & mutTaskPending = thisPtr->mutTaskPending;
        boost::condition_variable & condTaskPending = thisPtr->condTaskPending;

        std::list<ITask*> & taskRunning = thisPtr->taskRunning;
        boost::mutex & mutTaskRunning = thisPtr->mutTaskRunning;
        mylib::Semaphore & counterTaskRunning = thisPtr->counterTaskRunning;

        volatile bool & forceThreadShutdown = thisPtr->forceThreadShutdown;

        ITask* task = 0;


        for (;;) {
            {
                // WAIT FOR AN AVAILABLE PENDING TASK
                uniquelk lkPending(mutTaskPending);

                while (taskPending.empty() && false == forceThreadShutdown) {
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
                counterTaskRunning.release();
            }
        }
    }

};



#endif // _MY_EXEC_SERVICE_V2A_HPP_
