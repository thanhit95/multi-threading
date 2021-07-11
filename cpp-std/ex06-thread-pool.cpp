/*
THREAD POOL IMPLEMENTATION
*/


#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <chrono>



////////////////////////////////////////////////////////////////



// interface ITask
class ITask {
public:
    virtual ~ITask() = default;
    virtual void run() = 0;
};



class ThreadPool {
private:
    int numThreads = 0;
    std::vector<std::thread> lstTh;
    std::queue<ITask*> taskPending;
    std::atomic_int32_t counterTaskRunning;
    volatile bool forceThreadShutdown;

    std::mutex mutTaskPending;
    std::condition_variable condTaskPending;


public:
    ThreadPool() = default;
    ThreadPool(const ThreadPool& other) = delete;
    ThreadPool(const ThreadPool&& other) = delete;
    void operator=(const ThreadPool& other) = delete;
    void operator=(const ThreadPool&& other) = delete;


    void init(int numThreads) {
        shutdown();

        this->numThreads = numThreads;
        lstTh.resize(numThreads);
        counterTaskRunning.store(0);
        forceThreadShutdown = false;

        for (auto&& th : lstTh) {
            th = std::thread(threadRoutine, this);
        }
    }


    void submit(ITask* task) {
        mutTaskPending.lock();
        taskPending.push(task);
        mutTaskPending.unlock();

        condTaskPending.notify_one();
    }


    void waitTaskDone() {
        bool done = false;

        for (;;) {
            mutTaskPending.lock();

            if (0 == taskPending.size() && 0 == counterTaskRunning.load()) {
                done = true;
            }

            mutTaskPending.unlock();

            if (done) {
                break;
            }

            std::this_thread::yield();
        }
    }


    void shutdown() {
        mutTaskPending.lock();

        forceThreadShutdown = true;
        std::queue<ITask*>().swap(taskPending);

        mutTaskPending.unlock();

        condTaskPending.notify_all();

        for (auto&& th : lstTh) {
            th.join();
        }

        numThreads = 0;
        lstTh.clear();
    }


private:
    static void threadRoutine(ThreadPool* thisPtr) {
        auto&& mutTaskPending = thisPtr->mutTaskPending;
        auto&& condTaskPending = thisPtr->condTaskPending;
        auto&& taskPending = thisPtr->taskPending;
        auto&& counterTaskRunning = thisPtr->counterTaskRunning;
        auto&& forceThreadShutdown = thisPtr->forceThreadShutdown;

        for (;;) {
            // WAITING FOR A PENDING TASK
            std::unique_lock<std::mutex> lkTaskPending(mutTaskPending);

            while (0 == taskPending.size() && false == forceThreadShutdown) {
                condTaskPending.wait(lkTaskPending);
            }

            if (forceThreadShutdown) {
                // lkTaskPending.unlock(); // remember this statement
                break;
            }


            // GET THE TASK FROM THE PENDING QUEUE
            auto task = taskPending.front();
            taskPending.pop();


            ++counterTaskRunning;


            lkTaskPending.unlock();


            // DO THE TASK
            task->run();
            --counterTaskRunning;
        }
    }
};



////////////////////////////////////////////////////////////////



class MyTask : public ITask {
public:
    char id;

public:
    void run() override {
        std::cout << "Task " << id << " is starting" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(3));
        std::cout << "Task " << id << " is completed" << std::endl;
    }
};



int main() {
    constexpr int NUM_THREADS = 2;
    constexpr int NUM_TASKS = 5;


    ThreadPool threadPool;
    threadPool.init(NUM_THREADS);


    std::vector<MyTask> lstTasks(NUM_TASKS);

    for (int i = 0; i < NUM_TASKS; ++i)
        lstTasks[i].id = 'A' + i;


    for (auto&& task : lstTasks)
        threadPool.submit(&task);

    std::cout << "All tasks are submitted" << std::endl;


    threadPool.waitTaskDone();
    std::cout << "All tasks are completed" << std::endl;


    threadPool.shutdown();


    return 0;
}
