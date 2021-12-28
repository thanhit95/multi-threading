/*
THE PRODUCER-CONSUMER PROBLEM

SOLUTION TYPE B: USING SEMAPHORES
    Version B01: 1 slow producer, 1 fast consumer
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
};



void* producer(void* argVoid) {
    auto arg = (GlobalArg*)argVoid;
    auto qProduct = arg->qProduct;
    auto sem = arg->sem;

    int i = 1;

    for (;; ++i) {
        sem->waitEmpty();

        qProduct->push(i);
        sleep(1);

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

        sem->postEmpty();
    }

    pthread_exit(nullptr);
    return nullptr;
}



int main() {
    GlobalSemaphore sem;
    queue<int> qProduct;
    pthread_t tidProducer, tidConsumer;

    GlobalArg globalArg = { &qProduct, &sem };
    int ret = 0;


    sem.init(0, 1);


    ret = pthread_create(&tidProducer, nullptr, producer, &globalArg);
    ret = pthread_create(&tidConsumer, nullptr, consumer, &globalArg);

    ret = pthread_join(tidProducer, nullptr);
    ret = pthread_join(tidConsumer, nullptr);


    sem.destroy();


    return 0;
}
