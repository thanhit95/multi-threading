/*
THE READERS-WRITERS PROBLEM
*/


#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include "mytool-random.hpp"
using namespace std;



struct WriterArg {
    volatile int* resource;
    sem_t* semResource;
    int timeDelay;
    sem_t* semServiceQueue;
};



struct ReaderArg {
    volatile int* resource;
    sem_t* semResource;
    int* readerCount;
    pthread_mutex_t* mutReaderCount;
    int timeDelay;
    sem_t* semServiceQueue;
};



void* writerFunc(void* argVoid) {
    auto arg = (WriterArg*)argVoid;
    sleep(arg->timeDelay);

    sem_wait(arg->semServiceQueue);

    sem_wait(arg->semResource);

    sem_post(arg->semServiceQueue);

    int data = mytool::RandInt::staticGet() % 100;
    *(arg->resource) = data;
    cout << "Write " << data << endl;

    sem_post(arg->semResource);

    pthread_exit(nullptr);
    return nullptr;
}



void* readerFunc(void* argVoid) {
    auto arg = (ReaderArg*)argVoid;
    sleep(arg->timeDelay);


    // inrease reader count
    sem_wait(arg->semServiceQueue);
    pthread_mutex_lock(arg->mutReaderCount);

    ( *(arg->readerCount) ) += 1;

    if (1 == *(arg->readerCount))
        sem_wait(arg->semResource);

    pthread_mutex_unlock(arg->mutReaderCount);
    sem_post(arg->semServiceQueue);


    // do the reading
    int data = *(arg->resource);
    cout << "Read " << data << endl;


    // decrease reader count
    pthread_mutex_lock(arg->mutReaderCount);

    ( *(arg->readerCount) ) -= 1;

    if (0 == *(arg->readerCount))
        sem_post(arg->semResource);

    pthread_mutex_unlock(arg->mutReaderCount);


    pthread_exit(nullptr);
    return nullptr;
}



void prepareArguments(
    ReaderArg argReader[], WriterArg argWriter[],
    int numReaders, int numWriters,
    volatile int* resource,
    sem_t* semResource,
    int* readerCount,
    pthread_mutex_t* mutReaderCount,
    sem_t* semServiceQueue
)
{
    for (int i = 0; i < numReaders; ++i) {
        argReader[i].resource = resource;
        argReader[i].semResource = semResource;
        argReader[i].readerCount = readerCount;
        argReader[i].mutReaderCount = mutReaderCount;
        argReader[i].timeDelay = mytool::RandInt::staticGet() % 3;
        argReader[i].semServiceQueue = semServiceQueue;
    }

    for (int i = 0; i < numWriters; ++i) {
        argWriter[i].resource = resource;
        argWriter[i].semResource = semResource;
        argWriter[i].timeDelay = mytool::RandInt::staticGet() % 3;
        argWriter[i].semServiceQueue = semServiceQueue;
    }
}



int main() {
    volatile int resource = 0;

    sem_t semResource;
    sem_init(&semResource, 0, 1);

    int readerCount = 0;
    pthread_mutex_t mutexReaderCount = PTHREAD_MUTEX_INITIALIZER;

    sem_t semServiceQueue;
    sem_init(&semServiceQueue, 0, 1);


    constexpr int NUM_READERS = 8;
    constexpr int NUM_WRITERS = 6;

    pthread_t lstTidReader[NUM_READERS];
    pthread_t lstTidWriter[NUM_WRITERS];

    int ret = 0;


    // PREPARE ARGUMENTS
    ReaderArg argReader[NUM_READERS];
    WriterArg argWriter[NUM_WRITERS];

    prepareArguments(argReader, argWriter, NUM_READERS, NUM_WRITERS,
                     &resource, &semResource,
                     &readerCount, &mutexReaderCount,
                     &semServiceQueue);


    // CREATE THREADS
    for (int i = 0; i < NUM_READERS; ++i) {
        ret = pthread_create(&lstTidReader[i], nullptr, readerFunc, &argReader[i]);
    }

    for (int i = 0; i < NUM_WRITERS; ++i) {
        ret = pthread_create(&lstTidWriter[i], nullptr, writerFunc, &argWriter[i]);
    }


    // JOIN THREADS
    for (int i = 0; i < NUM_READERS; ++i) {
        ret = pthread_join(lstTidReader[i], nullptr);
    }

    for (int i = 0; i < NUM_WRITERS; ++i) {
        ret = pthread_join(lstTidWriter[i], nullptr);
    }


    // CLEAN UP
    ret = pthread_mutex_destroy(&mutexReaderCount);
    ret = sem_destroy(&semResource);
    ret = sem_destroy(&semServiceQueue);


    return 0;
}
