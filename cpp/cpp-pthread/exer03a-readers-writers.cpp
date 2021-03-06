/*
THE READERS-WRITERS PROBLEM
Solution for the first readers-writers problem
*/


#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include "../cpp-std/mylib-random.hpp"
using namespace std;



struct GlobalData {
    volatile int resource = 0;
    int readerCount = 0;

    pthread_mutex_t mutResource = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_t mutReaderCount = PTHREAD_MUTEX_INITIALIZER;
};



struct ThreadArg {
    GlobalData* g;
    int delayTime;
};



void* doTaskWriter(void* argVoid) {
    auto arg = (ThreadArg*) argVoid;
    GlobalData* g = arg->g;

    sleep(arg->delayTime);

    pthread_mutex_lock(&g->mutResource);

    g->resource = mylib::RandInt::get(100);
    cout << "Write " << g->resource << endl;

    pthread_mutex_unlock(&g->mutResource);

    pthread_exit(nullptr);
    return nullptr;
}



void* doTaskReader(void* argVoid) {
    auto arg = (ThreadArg*) argVoid;
    GlobalData* g = arg->g;

    sleep(arg->delayTime);


    // Increase reader count
    pthread_mutex_lock(&g->mutReaderCount);

    g->readerCount += 1;

    if (1 == g->readerCount)
        pthread_mutex_lock(&g->mutResource);

    pthread_mutex_unlock(&g->mutReaderCount);


    // Do the reading
    cout << "Read " << g->resource << endl;


    // Decrease reader count
    pthread_mutex_lock(&g->mutReaderCount);

    g->readerCount -= 1;

    if (0 == g->readerCount)
        pthread_mutex_unlock(&g->mutResource);

    pthread_mutex_unlock(&g->mutReaderCount);


    pthread_exit(nullptr);
    return nullptr;
}



void prepareArg(ThreadArg arg[], int numArg, GlobalData* g) {
    for (int i = 0; i < numArg; ++i) {
        arg[i].g = g;
        arg[i].delayTime = mylib::RandInt::get(3);
    }
}



int main() {
    GlobalData globalData;

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
        ret = pthread_create(&lstTidReader[i], nullptr, &doTaskReader, &argReader[i]);
    }

    for (int i = 0; i < NUM_WRITERS; ++i) {
        ret = pthread_create(&lstTidWriter[i], nullptr, &doTaskWriter, &argWriter[i]);
    }


    // JOIN THREADS
    for (int i = 0; i < NUM_READERS; ++i) {
        ret = pthread_join(lstTidReader[i], nullptr);
    }

    for (int i = 0; i < NUM_WRITERS; ++i) {
        ret = pthread_join(lstTidWriter[i], nullptr);
    }


    // CLEAN UP
    ret = pthread_mutex_destroy(&globalData.mutResource);
    ret = pthread_mutex_destroy(&globalData.mutReaderCount);


    return 0;
}
