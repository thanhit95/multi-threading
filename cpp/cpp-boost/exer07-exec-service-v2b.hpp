/*
MY EXECUTOR SERVICE

Version 2B: The executor service storing running tasks
- Method "waitTaskDone" uses a condition variable to synchronize.
*/



#ifndef _MY_EXEC_SERVICE_V2B_HPP_
#define _MY_EXEC_SERVICE_V2B_HPP_



#include <vector>
#include <list>
#include <queue>
#include <boost/thread.hpp>
#include "exer07-exec-service-itask.hpp"



class MyExecServiceV2B {

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
    boost::condition_variable condTaskRunning;

    volatile bool forceThreadShutdown;


public:
    MyExecServiceV2B(int numThreads) {
        init(numThreads);
    }


private:
    MyExecServiceV2B(const MyExecServiceV2B& other) : numThreads(0) { }
    void operator=(const MyExecServiceV2B& other) { }

#if __cplusplus >= 201103L || (defined(_MSC_VER) && _MSC_VER >= 1900)
    MyExecServiceV2B(const MyExecServiceV2B&& other) : numThreads(0) { }
    void operator=(const MyExecServiceV2B&& other) { }
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
            uniquelk lkPending(mutTaskPending);

            if (0 == taskPending.size()) {
                uniquelk lkRunning(mutTaskRunning);

                while (taskRunning.size() > 0)
                    condTaskRunning.wait(lkRunning);

                // no pending task and no running task
                break;
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
    static void threadWorkerFunc(MyExecServiceV2B* thisPtr) {
        std::queue<ITask*> & taskPending = thisPtr->taskPending;
        boost::mutex & mutTaskPending = thisPtr->mutTaskPending;
        boost::condition_variable & condTaskPending = thisPtr->condTaskPending;

        std::list<ITask*> & taskRunning = thisPtr->taskRunning;
        boost::mutex & mutTaskRunning = thisPtr->mutTaskRunning;
        boost::condition_variable & condTaskRunning = thisPtr->condTaskRunning;

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
                condTaskRunning.notify_one();
            }
        }
    }

};



#endif // _MY_EXEC_SERVICE_V2B_HPP_
