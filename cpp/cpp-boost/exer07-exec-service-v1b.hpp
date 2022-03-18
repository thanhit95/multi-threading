/*
MY EXECUTOR SERVICE

Version 1B: Simple executor service
- Method "waitTaskDone" uses a condition variable to synchronize.
*/



#ifndef _MY_EXEC_SERVICE_V1B_HPP_
#define _MY_EXEC_SERVICE_V1B_HPP_



#include <vector>
#include <queue>
#include <boost/thread.hpp>
#include "exer07-exec-service-itask.hpp"



class MyExecServiceV1B {

private:
    typedef boost::unique_lock<boost::mutex> uniquelk;


private:
    int numThreads;
    boost::thread_group lstTh;

    std::queue<ITask*> taskPending;
    boost::mutex mutTaskPending;
    boost::condition_variable condTaskPending;

    int counterTaskRunning;
    boost::mutex mutTaskRunning;
    boost::condition_variable condTaskRunning;

    volatile bool forceThreadShutdown;


public:
    MyExecServiceV1B(int numThreads) {
        init(numThreads);
    }


private:
    MyExecServiceV1B(const MyExecServiceV1B& other) : numThreads(0) { }
    void operator=(const MyExecServiceV1B& other) { }

#if __cplusplus >= 201103L || (defined(_MSC_VER) && _MSC_VER >= 1900)
    MyExecServiceV1B(const MyExecServiceV1B&& other) : numThreads(0) { }
    void operator=(const MyExecServiceV1B&& other) { }
#endif


private:
    void init(int numThreads) {
        // shutdown();

        this->numThreads = numThreads;
        counterTaskRunning = 0;
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

                while (counterTaskRunning > 0)
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
    static void threadWorkerFunc(MyExecServiceV1B* thisPtr) {
        std::queue<ITask*> & taskPending = thisPtr->taskPending;
        boost::mutex & mutTaskPending = thisPtr->mutTaskPending;
        boost::condition_variable & condTaskPending = thisPtr->condTaskPending;

        int & counterTaskRunning = thisPtr->counterTaskRunning;
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

                ++counterTaskRunning;
            }

            // DO THE TASK
            task->run();

            {
                uniquelk lkRunning(mutTaskRunning);
                --counterTaskRunning;

                if (0 == counterTaskRunning) {
                    condTaskRunning.notify_one();
                }
            }
        }
    }

};



#endif // _MY_EXEC_SERVICE_V1B_HPP_
