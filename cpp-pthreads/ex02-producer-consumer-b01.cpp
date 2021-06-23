/*
THE PRODUCER-CONSUMER PROBLEM

SOLUTION TYPE B - USING SEMAPHORE
    version b01: 1 slow producer, 1 fast consumer
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
};



void* producer(void *argVoid) {
    auto arg = (GlobalArg*)argVoid;
    auto pqProduct = arg->pqProduct;
    auto psem = arg->psem;

    int i = 1;

    for (;; ++i) {
        psem->waitEmptyCount();

        pqProduct->push(i);
        sleep(1);

        psem->postFillCount();
    }

    pthread_exit(nullptr);
    return (void*)0;
}



void* consumer(void *argVoid) {
    auto arg = (GlobalArg*)argVoid;
    auto pqProduct = arg->pqProduct;
    auto psem = arg->psem;

    int data;

    for (;;) {
        psem->waitFillCount();

        data = pqProduct->front();
        pqProduct->pop();

        cout << "consumer " << data << endl;

        psem->postEmptyCount();
    }

    pthread_exit(nullptr);
    return (void*)0;
}



int main() {
    pthread_t tidProduder, tidConsumer;

    queue<int> qProduct;
    GlobalSemaphore sem;
    sem.init(0, 1);

    int ret = 0;

    GlobalArg globalArg;
    globalArg.pqProduct = &qProduct;
    globalArg.psem = &sem;

    ret = pthread_create(&tidProduder, nullptr, producer, &globalArg);
    ret = pthread_create(&tidConsumer, nullptr, consumer, &globalArg);

    ret = pthread_join(tidProduder, nullptr);
    ret = pthread_join(tidConsumer, nullptr);

    sem.destroy();
    return 0;
}
