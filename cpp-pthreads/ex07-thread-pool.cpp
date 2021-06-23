#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <pthread.h>
#include <unistd.h>



////////////////////////////////////////////////////////////////



// interface ITask
class ITask {
public:
    virtual ~ITask() = default;
    virtual void run() = 0;
};



class ThreadPool;



struct ThreadArg {
    ITask *task = nullptr;
    int index = -1;
    ThreadPool *ptr = nullptr;
};



class ThreadPool {
private:
    int numThreads = 0;
    std::vector<pthread_t> lstTids;
    std::vector<ThreadArg> lstArgs;
    std::set<int> indexFreeThreads;
    std::queue<ITask*> pendingTasks;
    bool doneAllTasks;

    pthread_mutex_t mutPendingTasks = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_t mutIndexFreeThreads = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t condPendingTasks = PTHREAD_COND_INITIALIZER;

    /* mutPendingTasks is used for both pendingTasks and doneAllTasks */


public:
    ThreadPool() = default;
    ThreadPool(const ThreadPool &other) = delete;
    ThreadPool(const ThreadPool &&other) = delete;
    void operator=(const ThreadPool &other) = delete;
    void operator=(const ThreadPool &&other) = delete;


    void init(int numThreads) {
        destroy();

        this->numThreads = numThreads;
        lstTids.resize(numThreads);
        lstArgs.resize(numThreads);
        mutPendingTasks = PTHREAD_MUTEX_INITIALIZER;
        mutIndexFreeThreads = PTHREAD_MUTEX_INITIALIZER;
        condPendingTasks = PTHREAD_COND_INITIALIZER;
        doneAllTasks = false;

        for (int i = 0; i < numThreads; ++i) {
            indexFreeThreads.insert(i);
            lstArgs[i].index = i;
            lstArgs[i].task = nullptr;
            lstArgs[i].ptr = this;
        }

        for (int i = 0; i < numThreads; ++i) {
            pthread_create(&lstTids[i], nullptr, threadRoutine, &lstArgs[i]);
        }
    }


    void destroy() {
        numThreads = 0;
        lstTids.clear();
        lstArgs.clear();
        indexFreeThreads.clear();
        std::queue<ITask*>().swap(pendingTasks); // clear queue
        pthread_mutex_destroy(&mutPendingTasks);
        pthread_mutex_destroy(&mutIndexFreeThreads);
        pthread_cond_destroy(&condPendingTasks);
    }


    void submit(ITask *task) {
        pthread_mutex_lock(&mutPendingTasks);
        pendingTasks.push(task);
        pthread_mutex_unlock(&mutPendingTasks);

        pthread_cond_signal(&condPendingTasks);  // notify a threadRoutine, it will be waked up...
    }


    void waitTaskDone() {
        bool done = false;
        int ret = 0;

        for (;;) {
            pthread_mutex_lock(&mutPendingTasks);
            pthread_mutex_lock(&mutIndexFreeThreads);

            if (0 == pendingTasks.size() &&
                numThreads == indexFreeThreads.size()) {
                doneAllTasks = true;
            }

            pthread_mutex_unlock(&mutIndexFreeThreads);
            pthread_mutex_unlock(&mutPendingTasks);

            if (doneAllTasks) {
                break;
            }
        }

        // for (int i = 0; i < lstTids.size(); ++i) {
        //     // std::cout << "wating for joining thread index " << i << std::endl;
        //     pthread_mutex_unlock(&mutPendingTasks);
        //     pthread_cond_signal(&condPendingTasks);
        //     ret = pthread_join(lstTids[i], nullptr);
        // }

        for (int i = 0; i < lstTids.size(); ++i) {
            ret = pthread_cancel(lstTids[i]);
        }
    }


private:
    static bool checkRoutineDone(bool done, pthread_mutex_t *mutPendingTasks) {
        if (false == done)
            return false;

        pthread_mutex_unlock(mutPendingTasks);
        return true;
    }


    static void* threadRoutine(void *argVoid) {
        auto arg = (ThreadArg*)argVoid;
        auto mutPendingTasks = &arg->ptr->mutPendingTasks;
        auto condPendingTasks = &arg->ptr->condPendingTasks;
        auto mutIndexFreeThreads = &arg->ptr->mutIndexFreeThreads;
        auto pendingTasks = &arg->ptr->pendingTasks;
        auto indexFreeThreads = &arg->ptr->indexFreeThreads;
        auto doneAllTasks = &arg->ptr->doneAllTasks;

        for (;;) {
            // WAITING FOR A PENDING TASK
            pthread_mutex_lock(mutPendingTasks);

            if (checkRoutineDone(*doneAllTasks, mutPendingTasks)) break;

            while (pendingTasks->size() == 0 and false == (*doneAllTasks)) {
                pthread_cond_wait(condPendingTasks, mutPendingTasks);
            }

            if (checkRoutineDone(*doneAllTasks, mutPendingTasks)) break;


            // GET THE TASK FROM THE PENDING QUEUE
            auto task = pendingTasks->front();
            pendingTasks->pop();

            // pthread_mutex_unlock(mutPendingTasks);  // WRONG!!!


            // DO THE TASK
            pthread_mutex_lock(mutIndexFreeThreads);
            indexFreeThreads->erase(arg->index);
            pthread_mutex_unlock(mutIndexFreeThreads);

            // THE POSITION OF BELOW STATEMENT IS EXTREMELY IMPORTANT
            pthread_mutex_unlock(mutPendingTasks);

            task->run();

            pthread_mutex_lock(mutIndexFreeThreads);
            indexFreeThreads->insert(arg->index);
            pthread_mutex_unlock(mutIndexFreeThreads);
        }

        pthread_exit(nullptr);
        return (void*)0;
    }
};



////////////////////////////////////////////////////////////////



class MyTask : public ITask {
public:
    int id;

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
    std::vector<MyTask> lstTasks(NUM_TASKS);

    for (int i = 0; i < NUM_TASKS; ++i)
        lstTasks[i].id = i + 1;


    threadPool.init(NUM_THREADS);

    for (auto &task : lstTasks)
        threadPool.submit(&task);

    std::cout << "All tasks submitted" << std::endl;


    threadPool.waitTaskDone();
    std::cout << "All tasks completed" << std::endl;

    return 0;
}
