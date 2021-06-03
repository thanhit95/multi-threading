/*
PRODUCER - CONSUMER PROBLEM

SOLUTION TYPE B - USING SEMAPHORE
    version b02: 2 slow producers, 1 fast consumer
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
    int dataAddIndex = 0;
};



void* producer(void *voidArg) {
    auto arg = (GlobalArg*)voidArg;
    auto pqProduct = arg->pqProduct;
    auto psem = arg->psem;

    int i = 1;

    for (;; ++i) {
        psem->waitEmptyCount();

        pqProduct->push(i + arg->dataAddIndex);
        sleep(1);

        psem->postFillCount();
    }

    pthread_exit(nullptr);
    return (void*)0;
}



void *consumer(void *voidArg) {
    auto arg = (GlobalArg*)voidArg;
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
    pthread_t pidProduder[2];
    pthread_t pidConsumer;

    queue<int> qProduct;
    GlobalSemaphore sem;
    sem.init(0, 1);

    GlobalArg globalArg;
    globalArg.pqProduct = &qProduct;
    globalArg.psem = &sem;

    int ret = 0;


    GlobalArg globalArg01 = globalArg;
    globalArg01.dataAddIndex = 0;
    ret = pthread_create(&pidProduder[0], nullptr, producer, (void*)&globalArg01);

    GlobalArg globalArg02 = globalArg;
    globalArg02.dataAddIndex = 1000;
    ret = pthread_create(&pidProduder[1], nullptr, producer, (void*)&globalArg02);


    ret = pthread_create(&pidConsumer, nullptr, consumer, (void*)&globalArg);


    pthread_join(pidProduder[0], nullptr);
    pthread_join(pidProduder[1], nullptr);
    pthread_join(pidConsumer, nullptr);

    return 0;
}
