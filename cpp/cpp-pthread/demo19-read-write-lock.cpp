/*
READ-WRITE LOCKS

Lock for reading
    A thread can hold multiple concurrent read locks on the rwlock object
    (that is, successfully call the pthread_rwlock_rdlock subroutine n times).
    If so, the thread must perform matching unlocks
    (that is, it must call the pthread_rwlock_unlock subroutine n times).

    There is a function that supports non-blocking:
        pthread_rwlock_tryrdlock

Lock for writing
    The pthread_rwlock_wrlock subroutine applies a write lock to the read/write lock
    referenced by the rwlock object.
    The calling thread acquires the write lock if no other thread (reader or writer)
    holds the read/write lock on the rwlock object.
    Otherwise, the thread does not return from the pthread_rwlock_wrlock call
    until it can acquire the lock.

    There is a function that supports non-blocking:
        pthread_rwlock_trywrlock
*/


#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include "../cpp-std/mylib-random.hpp"
using namespace std;



volatile int resource = 0;
pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER;



void* readFunc(void* arg) {
    auto timeWait = *(int*) arg;
    sleep(timeWait);

    pthread_rwlock_rdlock(&rwlock);

    cout << "read: " << resource << endl;

    pthread_rwlock_unlock(&rwlock);

    pthread_exit(nullptr);
    return nullptr;
}



void* writeFunc(void* arg) {
    auto timeWait = *(int*) arg;
    sleep(timeWait);

    pthread_rwlock_wrlock(&rwlock);

    resource = mylib::RandInt::get(100);
    cout << "write: " << resource << endl;

    pthread_rwlock_unlock(&rwlock);

    pthread_exit(nullptr);
    return nullptr;
}



int main() {
    constexpr int NUM_THREADS_READ = 10;
    constexpr int NUM_THREADS_WRITE = 4;
    constexpr int NUM_ARGS = 3;

    pthread_t lstTidRead[NUM_THREADS_READ];
    pthread_t lstTidWrite[NUM_THREADS_WRITE];
    int lstArg[NUM_ARGS];
    int ret = 0;


    // INITIALIZE
    for (int i = 0; i < NUM_ARGS; ++i) {
        lstArg[i] = i;
    }


    // CREATE THREADS
    for (auto&& tid : lstTidRead) {
        int argIndex = mylib::RandInt::get(NUM_ARGS);
        ret = pthread_create(&tid, nullptr, readFunc, &lstArg[argIndex]);
    }

    for (auto&& tid : lstTidWrite) {
        int argIndex = mylib::RandInt::get(NUM_ARGS);
        ret = pthread_create(&tid, nullptr, writeFunc, &lstArg[argIndex]);
    }


    // JOIN THREADS
    for (auto&& tid : lstTidRead) {
        ret = pthread_join(tid, nullptr);
    }

    for (auto&& tid : lstTidWrite) {
        ret = pthread_join(tid, nullptr);
    }


    pthread_rwlock_destroy(&rwlock);
    return 0;
}
