/*
THE PRODUCER-CONSUMER PROBLEM

SOLUTION TYPE B - USING SEMAPHORE
    version b04: multi fast producers, multi slow consumers
*/


#include <iostream>
#include <queue>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
using namespace std;



struct GlobalSemaphore {
    sem_t fillCount;    // item produced
    sem_t emptyCount;   // remaining space in queue

    void init(int fillCount, int emptyCount) {
        sem_init(&this->fillCount, 0, fillCount);
        sem_init(&this->emptyCount, 0, emptyCount);
    }

    void destroy() {
        sem_destroy(&fillCount);
        sem_destroy(&emptyCount);
    }

    void waitFillCount() {
        sem_wait(&fillCount);
    }

    void waitEmptyCount() {
        sem_wait(&emptyCount);
    }

    void postFillCount() {
        sem_post(&fillCount);
    }

    void postEmptyCount() {
        sem_post(&emptyCount);
    }
};



struct GlobalArg {
    queue<int> *pqProduct;
    GlobalSemaphore *psem;
    int dataAddFactor = 0;
};



void* producer(void *argVoid) {
    auto arg = (GlobalArg*)argVoid;
    auto pqProduct = arg->pqProduct;
    auto psem = arg->psem;

    int i = 1;

    for (;; ++i) {
        psem->waitEmptyCount();

        pqProduct->push(i + arg->dataAddFactor);

        psem->postFillCount();
    }

    pthread_exit(nullptr);
    return (void*)0;
}



void *consumer(void *argVoid) {
    auto arg = (GlobalArg*)argVoid;
    auto pqProduct = arg->pqProduct;
    auto psem = arg->psem;

    int data;

    for (;;) {
        psem->waitFillCount();

        data = pqProduct->front();
        pqProduct->pop();

        cout << "consumer " << data << endl;
        sleep(1);

        psem->postEmptyCount();
    }

    pthread_exit(nullptr);
    return (void*)0;
}



int main() {
    constexpr int NUM_PRODUCERS = 3;
    constexpr int NUM_CONSUMERS = 2;

    pthread_t tidProduder[NUM_PRODUCERS];
    pthread_t tidConsumer[NUM_CONSUMERS];

    queue<int> qProduct;
    GlobalSemaphore sem;
    sem.init(0, 6);

    int ret = 0;


    // PREPARE ARGUMENTS
    GlobalArg argProd[NUM_PRODUCERS];
    for (int i = 0; i < NUM_PRODUCERS; ++i) {
        argProd[i].pqProduct = &qProduct;
        argProd[i].psem = &sem;
        argProd[i].dataAddFactor = i * 1000;
    }

    GlobalArg argCon;
    argCon.pqProduct = &qProduct;
    argCon.psem = &sem;


    // CREATE THREADS
    for (int i = 0; i < NUM_PRODUCERS; ++i) {
        ret = pthread_create(&tidProduder[i], nullptr, producer, (void*)&argProd[i]);
    }

    for (int i = 0; i < NUM_CONSUMERS; ++i) {
        ret = pthread_create(&tidConsumer[i], nullptr, consumer, (void*)&argCon);
    }


    // JOIN THREADS
    for (int i = 0; i < NUM_PRODUCERS; ++i) {
        ret = pthread_join(tidProduder[i], nullptr);
    }

    for (int i = 0; i < NUM_CONSUMERS; ++i) {
        ret = pthread_join(tidConsumer[i], nullptr);
    }


    return 0;
}
