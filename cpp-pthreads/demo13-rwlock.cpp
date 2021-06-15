/*
READ/WRITE LOCK

In many situations, data is read more often than it is modified or written.
In these cases, you can allow threads to read concurrently while holding the lock
and allow only one thread to hold the lock when data is modified.
A multiple-reader single-writer lock (or read/write lock) does this.
A read/write lock is acquired either for reading or writing, and then is released.
The thread that acquires the read-write lock must be the one that releases it.

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
#include <pthread.h>
#include <unistd.h>
#include "mytool-random.hpp"

using namespace std;



pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER;
mytool::RandIntGenerator intGen;



struct RoutineArg {
    int *resource = nullptr;
    int waitTime = 0;
};



void* routineRead(void *argVoid) {
    auto arg = (RoutineArg*)argVoid;
    sleep(arg->waitTime);

    pthread_rwlock_rdlock(&rwlock);

    int value = *(arg->resource);
    cout << "routineRead: " << value << endl;

    pthread_rwlock_unlock(&rwlock);

    pthread_exit(nullptr);
    return (void*)0;
}



void* routineWrite(void *argVoid) {
    auto arg = (RoutineArg*)argVoid;
    sleep(arg->waitTime);

    pthread_rwlock_wrlock(&rwlock);

    int value = intGen.get();
    *(arg->resource) = value;
    cout << "routineWrite: " << value << endl;

    pthread_rwlock_unlock(&rwlock);

    pthread_exit(nullptr);
    return (void*)0;
}



int main() {
    constexpr int NUM_THREADS_READ = 7;
    constexpr int NUM_THREADS_WRITE = 2;
    constexpr int NUM_ARGS = 3;

    pthread_t tidRead[NUM_THREADS_READ];
    pthread_t tidWrite[NUM_THREADS_WRITE];

    int resource = 0;
    RoutineArg arg[NUM_ARGS];

    int ret = 0;


    // INITIALIZE
    // pthread_rwlock_init(&rwlock, nullptr);
    intGen.init(1, 100);

    for (auto &argItem : arg) {
        argItem.resource = &resource;
        argItem.waitTime = 1 + (intGen.get() % 4);
    }


    // CREATE THREADS
    for (int i = 0; i < NUM_THREADS_READ; ++i) {
        int argIndex = intGen.get() % NUM_ARGS;
        ret = pthread_create(&tidRead[i], nullptr, routineRead, (void*)&arg[argIndex]);
    }

    for (int i = 0; i < NUM_THREADS_WRITE; ++i) {
        int argIndex = intGen.get() % NUM_ARGS;
        ret = pthread_create(&tidWrite[i], nullptr, routineWrite, (void*)&arg[argIndex]);
    }


    // JOIN THREADS
    for (int i = 0; i < NUM_THREADS_WRITE; ++i) {
        ret = pthread_join(tidWrite[i], nullptr);
    }

    for (int i = 0; i < NUM_THREADS_READ; ++i) {
        ret = pthread_join(tidRead[i], nullptr);
    }


    pthread_rwlock_destroy(&rwlock);
    return 0;
}
