/*
SYNCHRONIZED BLOCKS

Synchronized blocks in C++ POSIX threading are not supported by default.
To demonstate synchronized blocks, I implement the class LockGuard.

Now, let's see the code:
    {
        LockGuard lk(&mutex);
        // do something in the critical section
    }

When go to the end of the code block, lk object shall execute it's destructor and release mutex.
*/


#include <iostream>
#include <unistd.h>
#include <pthread.h>
using namespace std;



class LockGuard {

private:
    pthread_mutex_t *mut = nullptr;

private:
    LockGuard(const LockGuard&) = delete;
    LockGuard(const LockGuard&&) = delete;
    void operator=(const LockGuard&) = delete;
    void operator=(const LockGuard&&) = delete;

public:
    LockGuard(pthread_mutex_t *mut) {
        this->mut = mut; // assume that mut != nullptr
        pthread_mutex_lock(this->mut);
    }

    ~LockGuard() {
        pthread_mutex_unlock(this->mut);
    }

};



pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
int counter = 0;



void* doTask(void*) {
    sleep(1);

    // This is the "synchronized block"
    {
        LockGuard lk(&mut);

        for (int i = 0; i < 10000; ++i)
            ++counter;
    }

    pthread_exit(nullptr);
    return nullptr;
}



int main() {
    constexpr int NUM_THREADS = 3;
    pthread_t lstTid[NUM_THREADS];
    int ret = 0;


    for (auto&& tid : lstTid) {
        ret = pthread_create(&tid, nullptr, doTask, nullptr);
    }


    for (auto&& tid : lstTid) {
        ret = pthread_join(tid, nullptr);
    }


    cout << "counter = " << counter << endl;


    ret = pthread_mutex_destroy(&mut);
    return 0;
}
