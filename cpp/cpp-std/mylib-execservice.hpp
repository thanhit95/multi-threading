/******************************************************
*
* File name:    mylib-execservice.hpp
*
* Author:       Name:   Thanh Nguyen
*               Email:  thanh.it1995(at)gmail(dot)com
*
* License:      3-Clause BSD License
*
* Description:  The executor service implementation in C++11 std threading
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
#include <thread>
#include <mutex>
#include <condition_variable>



namespace mylib {



class ExecService {

private:
    using uniquelk = std::unique_lock<std::mutex>;


public:
    using taskFunc = std::function<void()>;


private:
    int numThreads = 0;
    std::vector<std::thread> lstTh;

    std::queue<taskFunc> taskPending;
    std::mutex mutTaskPending;
    std::condition_variable condTaskPending;

    int counterTaskRunning;
    std::mutex mutTaskRunning;
    std::condition_variable condTaskRunning;

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

        this->numThreads = numThreads;
        lstTh.resize(numThreads);
        counterTaskRunning = 0;
        forceThreadShutdown = false;

        for (auto&& th : lstTh) {
            th = std::thread(&threadWorkerFunc, this);
        }
    }


public:
    void submit(taskFunc task) {
        {
            uniquelk lk(mutTaskPending);
            taskPending.push(task);
        }

        condTaskPending.notify_one();
    }


    void waitTaskDone() {
        for (;;) {
            uniquelk lkPending(mutTaskPending);

            if (taskPending.empty()) {
                uniquelk lkRunning(mutTaskRunning);

                condTaskRunning.wait(lkRunning, [&] { return counterTaskRunning <= 0; });

                // no pending task and no running task
                break;
            }
        }
    }


    void shutdown() {
        {
            uniquelk lk(mutTaskPending);
            forceThreadShutdown = true;
            std::queue<taskFunc>().swap(taskPending);
        }

        condTaskPending.notify_all();

        for (auto&& th : lstTh) {
            th.join();
        }

        numThreads = 0;
        lstTh.clear();
    }


private:
    static void threadWorkerFunc(ExecService* thisPtr) {
        auto&& taskPending = thisPtr->taskPending;
        auto&& mutTaskPending = thisPtr->mutTaskPending;
        auto&& condTaskPending = thisPtr->condTaskPending;

        auto&& counterTaskRunning = thisPtr->counterTaskRunning;
        auto&& mutTaskRunning = thisPtr->mutTaskRunning;
        auto&& condTaskRunning = thisPtr->condTaskRunning;

        auto&& forceThreadShutdown = thisPtr->forceThreadShutdown;

        taskFunc task = nullptr;


        for (;;) {
            {
                // WAIT FOR AN AVAILABLE PENDING TASK
                uniquelk lkPending(mutTaskPending);

                condTaskPending.wait(lkPending, [&] {
                    return forceThreadShutdown || !taskPending.empty();
                });

                if (forceThreadShutdown) {
                    break;
                }

                // GET THE TASK FROM THE PENDING QUEUE
                task = taskPending.front();
                taskPending.pop();

                ++counterTaskRunning;
            }

            // DO THE TASK
            task();

            {
                uniquelk lkRunning(mutTaskRunning);
                --counterTaskRunning;

                if (0 == counterTaskRunning) {
                    condTaskRunning.notify_one();
                }
            }
        }
    }

}; // ExecService



} // namespace mylib



#endif // _MYLIB_EXEC_SERVICE_HPP_
