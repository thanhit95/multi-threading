/*
THE PRODUCER-CONSUMER PROBLEM

SOLUTION TYPE B: USING SEMAPHORES
    Version B03: 2 fast producers, 1 slow consumer
*/


#include <iostream>
#include <queue>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
using namespace std;



struct GlobalSemaphore {
    sem_t semFill;      // item produced
    sem_t semEmpty;     // remaining space in queue

    void init(int semFillValue, int semEmptyValue) {
        sem_init(&semFill, 0, semFillValue);
        sem_init(&semEmpty, 0, semEmptyValue);
    }

    void destroy() {
        sem_destroy(&semFill);
        sem_destroy(&semEmpty);
    }

    void waitFill() {
        sem_wait(&semFill);
    }

    void waitEmpty() {
        sem_wait(&semEmpty);
    }

    void postFill() {
        sem_post(&semFill);
    }

    void postEmpty() {
        sem_post(&semEmpty);
    }
};



struct GlobalArg {
    queue<int>* qProduct;
    GlobalSemaphore* sem;
    int startValue;
};



void* producer(void* argVoid) {
    auto arg = (GlobalArg*)argVoid;
    auto qProduct = arg->qProduct;
    auto sem = arg->sem;

    int i = 1;

    for (;; ++i) {
        sem->waitEmpty();

        qProduct->push(i + arg->startValue);

        sem->postFill();
    }

    pthread_exit(nullptr);
    return nullptr;
}



void* consumer(void* argVoid) {
    auto arg = (GlobalArg*)argVoid;
    auto qProduct = arg->qProduct;
    auto sem = arg->sem;

    int data = 0;

    for (;;) {
        sem->waitFill();

        data = qProduct->front();
        qProduct->pop();

        cout << "Consumer " << data << endl;
        sleep(1);

        sem->postEmpty();
    }

    pthread_exit(nullptr);
    return nullptr;
}



int main() {
    GlobalSemaphore sem;
    queue<int> qProduct;
    pthread_t tidProducerA, tidProducerB, tidConsumer;

    GlobalArg argCon, argProA, argProB;
    int ret = 0;


    sem.init(0, 1);


    argCon = argProA = argProB = { &qProduct, &sem, 0 };
    argProA.startValue = 0;
    argProB.startValue = 1000;


    ret = pthread_create(&tidProducerA, nullptr, producer, &argProA);
    ret = pthread_create(&tidProducerB, nullptr, producer, &argProB);
    ret = pthread_create(&tidConsumer, nullptr, consumer, &argCon);

    ret = pthread_join(tidProducerA, nullptr);
    ret = pthread_join(tidProducerB, nullptr);
    ret = pthread_join(tidConsumer, nullptr);


    sem.destroy();


    return 0;
}
