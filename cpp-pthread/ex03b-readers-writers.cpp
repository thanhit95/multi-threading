/*
THE READERS-WRITERS PROBLEM
Solution for the third readers-writers problem
*/


#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include "mytool-random.hpp"
using namespace std;



struct GlobalData {
    volatile int resource = 0;
    sem_t semResource;

    int readerCount = 0;
    pthread_mutex_t mutReaderCount = PTHREAD_MUTEX_INITIALIZER;

    sem_t semServiceQueue;
};



struct ThreadArg {
    GlobalData* g;
    int timeDelay;
};



void* writerFunc(void* argVoid) {
    auto arg = (ThreadArg*)argVoid;
    GlobalData* g = arg->g;

    sleep(arg->timeDelay);

    sem_wait(&g->semServiceQueue);

    sem_wait(&g->semResource);

    sem_post(&g->semServiceQueue);

    g->resource = mytool::RandInt::staticGet() % 100;
    cout << "Write " << g->resource << endl;

    sem_post(&g->semResource);

    pthread_exit(nullptr);
    return nullptr;
}



void* readerFunc(void* argVoid) {
    auto arg = (ThreadArg*)argVoid;
    GlobalData* g = arg->g;

    sleep(arg->timeDelay);


    // inrease reader count
    sem_wait(&g->semServiceQueue);
    pthread_mutex_lock(&g->mutReaderCount);

    g->readerCount += 1;

    if (1 == g->readerCount)
        sem_wait(&g->semResource);

    pthread_mutex_unlock(&g->mutReaderCount);
    sem_post(&g->semServiceQueue);


    // do the reading
    cout << "Read " << g->resource << endl;


    // decrease reader count
    pthread_mutex_lock(&g->mutReaderCount);

    g->readerCount -= 1;

    if (0 == g->readerCount)
        sem_post(&g->semResource);

    pthread_mutex_unlock(&g->mutReaderCount);


    pthread_exit(nullptr);
    return nullptr;
}



void prepareArg(ThreadArg arg[], int numArg, GlobalData* g) {
    for (int i = 0; i < numArg; ++i) {
        arg[i].g = g;
        arg[i].timeDelay = mytool::RandInt::staticGet() % 3;
    }
}



int main() {
    GlobalData globalData;
    sem_init(&globalData.semResource, 0, 1);
    sem_init(&globalData.semServiceQueue, 0, 1);


    constexpr int NUM_READERS = 8;
    constexpr int NUM_WRITERS = 6;

    pthread_t lstTidReader[NUM_READERS];
    pthread_t lstTidWriter[NUM_WRITERS];

    int ret = 0;


    // PREPARE ARGUMENTS
    ThreadArg argReader[NUM_READERS];
    ThreadArg argWriter[NUM_WRITERS];

    prepareArg(argReader, NUM_READERS, &globalData);
    prepareArg(argWriter, NUM_WRITERS, &globalData);


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
    ret = sem_destroy(&globalData.semResource);
    ret = pthread_mutex_destroy(&globalData.mutReaderCount);
    ret = sem_destroy(&globalData.semServiceQueue);


    return 0;
}
