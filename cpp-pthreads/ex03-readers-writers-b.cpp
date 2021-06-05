/*
THE READERS-WRITERS PROBLEM


PROBLEM STATEMENT
    SECOND READERS-WRITER PROBLEM
        The first solution is suboptimal, because it is possible that a reader R1 might have the lock,
        a writer W be waiting for the lock, and then a reader R2 requests access.
        It would be unfair for R2 to jump in immediately, ahead of W;
        if that happened often enough, W would STARVE.
        Instead, W should start as soon as possible.
        This is the motivation for the second readers–writers problem, in which the constraint is
        added that no writer, once added to the queue, shall be kept waiting longer than absolutely necessary.
        This is also called writers-preference.


    THIRD READERS-WRITER PROBLEM
        In fact, the solutions implied by both problem statements can result in starvation
        - the first one may starve writers in the queue, and the second one may starve readers.
        Therefore, the third readers–writers problem is sometimes proposed, which adds the constraint that
        no thread shall be allowed to starve;
        that is, the operation of obtaining a lock on the shared data will always terminate
        in a bounded amount of time.


SOLUTION FOR THE THIRD READERS-WRITER PROBLEM
    The idea is using a semaphore "serviceQueue" to preserve ordering of requests (signaling must be FIFO).
*/


#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include "mytool-random.hpp"

using namespace std;
using namespace mytool;



struct WriterArg {
    int *pResource;
    sem_t *pSemResource;
    sem_t *pSemServiceQueue;
    RandIntGenerator *pRandInt;
    int delayTime;
};



struct ReaderArg {
    int *pResource;
    sem_t *pSemResource;
    sem_t *pSemServiceQueue;
    int *pReaderCount;
    pthread_mutex_t *pMutReaderCount;
    int delayTime;
};



void* writerFunc(void *argVoid) {
    auto arg = (WriterArg*)argVoid;
    sleep(arg->delayTime);

    sem_wait(arg->pSemServiceQueue);

    sem_wait(arg->pSemResource);

    sem_post(arg->pSemServiceQueue);

    int data = arg->pRandInt->get();
    *(arg->pResource) = data;
    cout << "write " << data << endl;

    sem_post(arg->pSemResource);

    pthread_exit(nullptr);
    return (void*)0;
}



void* readerFunc(void *argVoid) {
    auto arg = (ReaderArg*)argVoid;
    sleep(arg->delayTime);


    // inrease reader count
    sem_wait(arg->pSemServiceQueue);
    pthread_mutex_lock(arg->pMutReaderCount);

    ( *(arg->pReaderCount) ) += 1;

    if (1 == *(arg->pReaderCount))
        sem_wait(arg->pSemResource);

    sem_post(arg->pSemServiceQueue);
    pthread_mutex_unlock(arg->pMutReaderCount);


    // do the reading
    int data = *(arg->pResource);
    cout << "read " << data << endl;


    // decrease reader count
    pthread_mutex_lock(arg->pMutReaderCount);

    ( *(arg->pReaderCount) ) -= 1;

    if (0 == *(arg->pReaderCount))
        sem_post(arg->pSemResource);

    pthread_mutex_unlock(arg->pMutReaderCount);


    pthread_exit(nullptr);
    return (void*)0;
}



void prepareArguments(
    ReaderArg argReader[], WriterArg argWriter[],
    int numReaders, int numWriters,
    int *pResource,
    sem_t *pSemResource,
    sem_t *pSemServiceQueue,
    int *pReaderCount,
    pthread_mutex_t *pMutReaderCount,
    RandIntGenerator *pRandInt
)
{
    RandIntGenerator delayTimeGen(0, 2);

    for (int i = 0; i < numReaders; ++i) {
        argReader[i].pResource = pResource;
        argReader[i].pSemResource = pSemResource;
        argReader[i].pSemServiceQueue = pSemServiceQueue;
        argReader[i].pReaderCount = pReaderCount;
        argReader[i].pMutReaderCount = pMutReaderCount;
        argReader[i].delayTime = delayTimeGen.get();
    }

    for (int i = 0; i < numWriters; ++i) {
        argWriter[i].pResource = pResource;
        argWriter[i].pSemResource = pSemResource;
        argWriter[i].pSemServiceQueue = pSemServiceQueue;
        argWriter[i].pRandInt = pRandInt;
        argWriter[i].delayTime = delayTimeGen.get();
    }
}



int main() {
    int resource = 0;

    constexpr int NUM_READERS = 8;
    constexpr int NUM_WRITERS = 8;

    pthread_t tidReader[NUM_READERS];
    pthread_t tidWriter[NUM_WRITERS];

    sem_t semResource;
    sem_t semServiceQueue;

    sem_init(&semResource, 0, 1);
    sem_init(&semServiceQueue, 0, 1);

    pthread_mutex_t mutexReaderCount = PTHREAD_MUTEX_INITIALIZER;

    int readerCount = 0;

    RandIntGenerator randInt(0, 100);
    int ret = 0;


    // PREPARE ARGUMENTS
    ReaderArg argReader[NUM_READERS];
    WriterArg argWriter[NUM_WRITERS];

    prepareArguments(argReader, argWriter, NUM_READERS, NUM_WRITERS,
                     &resource, &semResource,
                     &semServiceQueue,
                     &readerCount, &mutexReaderCount,
                     &randInt);


    // CREATE THREADS
    for (int i = 0; i < NUM_READERS; ++i) {
        ret = pthread_create(&tidReader[i], nullptr, readerFunc, (void*)&argReader[i]);
    }

    for (int i = 0; i < NUM_WRITERS; ++i) {
        ret = pthread_create(&tidWriter[i], nullptr, writerFunc, (void*)&argWriter[i]);
    }


    // JOIN THREADS
    for (int i = 0; i < NUM_READERS; ++i) {
        ret = pthread_join(tidReader[i], nullptr);
    }

    for (int i = 0; i < NUM_WRITERS; ++i) {
        ret = pthread_join(tidWriter[i], nullptr);
    }


    // CLEAN UP
    pthread_mutex_destroy(&mutexReaderCount);
    sem_destroy(&semResource);
    sem_destroy(&semServiceQueue);


    return 0;
}
