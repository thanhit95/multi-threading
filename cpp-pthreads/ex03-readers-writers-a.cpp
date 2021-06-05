/*
THE READERS-WRITERS PROBLEM


PROBLEM STATEMENT
    Consider a situation where we have a file shared between many people.

    If one of the people tries editing the file, no other person should be reading or writing
    at the same time, otherwise changes will not be visible to him/her.
    However if some person is reading the file, then others may read it at the same time.

    Precisely in Computer Science we call this situation as the readers-writers problem.

    What's the problem here?
    - One set of data is shared among a number of processes.
    - Once a writer is ready, it performs its write. Only one writer may write at a time.
    - If a process is writing, no other process can read it.
    - If at least one reader is reading, no other process can write.

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
    RandIntGenerator *pRandInt;
    int delayTime;
};



struct ReaderArg {
    int *pResource;
    sem_t *pSemResource;
    int *pReaderCount;
    pthread_mutex_t *pMutReaderCount;
    int delayTime;
};



void* writerFunc(void *argVoid) {
    auto arg = (WriterArg*)argVoid;
    sleep(arg->delayTime);

    sem_wait(arg->pSemResource);

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
    pthread_mutex_lock(arg->pMutReaderCount);

    ( *(arg->pReaderCount) ) += 1;

    if (1 == *(arg->pReaderCount))
        sem_wait(arg->pSemResource);

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
    int *pReaderCount,
    pthread_mutex_t *pMutReaderCount,
    RandIntGenerator *pRandInt
)
{
    RandIntGenerator delayTimeGen(0, 2);

    for (int i = 0; i < numReaders; ++i) {
        argReader[i].pResource = pResource;
        argReader[i].pSemResource = pSemResource;
        argReader[i].pReaderCount = pReaderCount;
        argReader[i].pMutReaderCount = pMutReaderCount;
        argReader[i].delayTime = delayTimeGen.get();
    }

    for (int i = 0; i < numWriters; ++i) {
        argWriter[i].pResource = pResource;
        argWriter[i].pSemResource = pSemResource;
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
    sem_init(&semResource, 0, 1);

    pthread_mutex_t mutexReaderCount = PTHREAD_MUTEX_INITIALIZER;

    int readerCount = 0;

    RandIntGenerator randInt(0, 100);
    int ret = 0;


    // PREPARE ARGUMENTS
    ReaderArg argReader[NUM_READERS];
    WriterArg argWriter[NUM_WRITERS];

    prepareArguments(argReader, argWriter, NUM_READERS, NUM_WRITERS,
                     &resource, &semResource,
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


    return 0;
}
