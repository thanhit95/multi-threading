/*
THE PRODUCER-CONSUMER PROBLEM

SOLUTION TYPE B - USING SEMAPHORE
    version b03: 2 fast producers, 1 slow consumer
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
    return nullptr;
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
        sleep(1);

        psem->postEmptyCount();
    }

    pthread_exit(nullptr);
    return nullptr;
}



int main() {
    pthread_t tidProduder[2];
    pthread_t tidConsumer;

    queue<int> qProduct;
    GlobalSemaphore sem;
    sem.init(0, 4);

    int ret = 0;


    GlobalArg argCon;
    argCon.pqProduct = &qProduct;
    argCon.psem = &sem;

    GlobalArg argProd0, argProd1;
    argProd0 = argProd1 = argCon;
    argProd0.dataAddFactor = 0;
    argProd1.dataAddFactor = 1000;


    ret = pthread_create(&tidProduder[0], nullptr, producer, &argProd0);
    ret = pthread_create(&tidProduder[1], nullptr, producer, &argProd1);
    ret = pthread_create(&tidConsumer, nullptr, consumer, &argCon);

    ret = pthread_join(tidProduder[0], nullptr);
    ret = pthread_join(tidProduder[1], nullptr);
    ret = pthread_join(tidConsumer, nullptr);


    sem.destroy();
    return 0;
}
