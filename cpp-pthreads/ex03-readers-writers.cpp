#include <iostream>
#include <random>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

using namespace std;



class RandomNumberGen {
private:
    std::random_device rd;
    std::mt19937 mt;
    std::uniform_int_distribution<int> dist;


public:
    RandomNumberGen(int minValue, int maxValue): dist(minValue, maxValue) {
        mt.seed(rd());
    }


    int get() {
        return dist(mt);
    }
};



struct WriterArg {
    int *pResource;
    sem_t *pSemResource;
    RandomNumberGen *pNumberGen;
    int delayTime;
};



struct ReaderArg {
    int *pResource;
    sem_t *pSemResource;
    int *pReaderCount;
    pthread_mutex_t *pMutexRc;
    int delayTime;
};



void* writerFunc(void *argVoid) {
    auto arg = (WriterArg*)argVoid;
    sleep(arg->delayTime);

    sem_wait(arg->pSemResource);

    int data = arg->pNumberGen->get();
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
    pthread_mutex_lock(arg->pMutexRc);

    ( *(arg->pReaderCount) ) += 1;

    if (1 == *(arg->pReaderCount))
        sem_wait(arg->pSemResource);

    pthread_mutex_unlock(arg->pMutexRc);


    // do the reading
    int data = *(arg->pResource);
    cout << "read " << data << endl;


    // decrease reader count
    pthread_mutex_lock(arg->pMutexRc);

    ( *(arg->pReaderCount) ) -= 1;

    if (0 == *(arg->pReaderCount))
        sem_post(arg->pSemResource);

    pthread_mutex_unlock(arg->pMutexRc);


    pthread_exit(nullptr);
    return (void*)0;
}



void prepareArguments(
    ReaderArg argReader[], WriterArg argWriter[],
    int numReaders, int numWriters,
    int *pResource,
    sem_t *pSemResource,
    int *pReaderCount,
    pthread_mutex_t *pMutexRc,
    RandomNumberGen *pNumberGen
)
{
    RandomNumberGen delayTimeGen(0, 2);

    for (int i = 0; i < numReaders; ++i) {
        argReader[i].pResource = pResource;
        argReader[i].pSemResource = pSemResource;
        argReader[i].pReaderCount = pReaderCount;
        argReader[i].pMutexRc = pMutexRc;
        argReader[i].delayTime = delayTimeGen.get();
    }

    for (int i = 0; i < numWriters; ++i) {
        argWriter[i].pResource = pResource;
        argWriter[i].pSemResource = pSemResource;
        argWriter[i].pNumberGen = pNumberGen;
        argWriter[i].delayTime = delayTimeGen.get();
    }
}



int main() {
    int resource = 0;

    constexpr int NUM_READERS = 8;
    constexpr int NUM_WRITERS = 8;

    pthread_t pidReader[NUM_READERS];
    pthread_t pidWriter[NUM_WRITERS];

    sem_t semResource;
    sem_init(&semResource, 0, 1);

    pthread_mutex_t mutexRc = PTHREAD_MUTEX_INITIALIZER;

    int readerCount = 0;

    RandomNumberGen numberGen(0, 100);
    int ret = 0;


    // PREPARE ARGUMENTS
    ReaderArg argReader[NUM_READERS];
    WriterArg argWriter[NUM_WRITERS];

    prepareArguments(argReader, argWriter, NUM_READERS, NUM_WRITERS,
                     &resource, &semResource,
                     &readerCount, &mutexRc,
                     &numberGen);


    // CREATE THREADS
    for (int i = 0; i < NUM_READERS; ++i) {
        ret = pthread_create(&pidReader[i], nullptr, readerFunc, (void*)&argReader[i]);
    }

    for (int i = 0; i < NUM_WRITERS; ++i) {
        ret = pthread_create(&pidWriter[i], nullptr, writerFunc, (void*)&argWriter[i]);
    }


    // JOIN THREADS
    for (int i = 0; i < NUM_READERS; ++i) {
        ret = pthread_join(pidReader[i], nullptr);
    }

    for (int i = 0; i < NUM_WRITERS; ++i) {
        ret = pthread_join(pidWriter[i], nullptr);
    }


    return 0;
}
