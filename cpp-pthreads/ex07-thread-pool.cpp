/*
THREAD POOL IMPLEMENTATION
*/


#include <iostream>
#include <vector>
#include <queue>
#include <atomic>
#include <pthread.h>
#include <unistd.h>



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
    std::vector<pthread_t> lstTh;
    std::queue<ITask*> taskPending;
    std::atomic_int32_t counterTaskRunning;
    volatile bool forceThreadShutdown;

    pthread_mutex_t mutTaskPending = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t condTaskPending = PTHREAD_COND_INITIALIZER;


public:
    ThreadPool() = default;
    ThreadPool(const ThreadPool& other) = delete;
    ThreadPool(const ThreadPool&& other) = delete;
    void operator=(const ThreadPool& other) = delete;
    void operator=(const ThreadPool&& other) = delete;


    void init(int numThreads) {
        int ret = 0;

        shutdown();

        mutTaskPending = PTHREAD_MUTEX_INITIALIZER;
        condTaskPending = PTHREAD_COND_INITIALIZER;

        this->numThreads = numThreads;
        lstTh.resize(numThreads);
        counterTaskRunning.store(0);
        forceThreadShutdown = false;

        for (auto&& th : lstTh) {
            ret = pthread_create(&th, nullptr, threadRoutine, this);
        }
    }


    void submit(ITask* task) {
        pthread_mutex_lock(&mutTaskPending);
        taskPending.push(task);
        pthread_mutex_unlock(&mutTaskPending);

        pthread_cond_signal(&condTaskPending);
    }


    void waitTaskDone() {
        bool done = false;

        for (;;) {
            pthread_mutex_lock(&mutTaskPending);

            if (0 == taskPending.size() && 0 == counterTaskRunning.load()) {
                done = true;
            }

            pthread_mutex_unlock(&mutTaskPending);

            if (done) {
                break;
            }

            pthread_yield();
        }
    }


    void shutdown() {
        pthread_mutex_lock(&mutTaskPending);

        forceThreadShutdown = true;
        std::queue<ITask*>().swap(taskPending);

        pthread_mutex_unlock(&mutTaskPending);

        pthread_cond_broadcast(&condTaskPending);

        for (auto&& th : lstTh) {
            pthread_join(th, nullptr);
        }

        numThreads = 0;
        lstTh.clear();

        pthread_mutex_destroy(&mutTaskPending);
        pthread_cond_destroy(&condTaskPending);
    }


private:
    static void* threadRoutine(void* argVoid) {
        auto thisPtr = (ThreadPool*)argVoid;
        auto&& mutTaskPending = thisPtr->mutTaskPending;
        auto&& condTaskPending = thisPtr->condTaskPending;
        auto&& taskPending = thisPtr->taskPending;
        auto&& counterTaskRunning = thisPtr->counterTaskRunning;
        auto&& forceThreadShutdown = thisPtr->forceThreadShutdown;

        for (;;) {
            // WAITING FOR A PENDING TASK
            pthread_mutex_lock(&mutTaskPending);

            while (taskPending.size() == 0 and false == forceThreadShutdown) {
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
            task->run();
            --counterTaskRunning;
        }

        pthread_exit(nullptr);
        return nullptr;
    }
};



////////////////////////////////////////////////////////////////



class MyTask : public ITask {
public:
    char id;

public:
    void run() override {
        std::cout << "Task " << id << " starting" << std::endl;
        sleep(3);
        std::cout << "Task " << id << " completed" << std::endl;
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

    std::cout << "All tasks submitted" << std::endl;


    threadPool.waitTaskDone();
    std::cout << "All tasks completed" << std::endl;


    threadPool.shutdown();


    return 0;
}
