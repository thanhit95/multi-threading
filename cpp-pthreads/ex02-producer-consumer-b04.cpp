/*
THE PRODUCER-CONSUMER PROBLEM

SOLUTION TYPE B - USING SEMAPHORE
    Version B04: multiple fast producers, multiple slow consumers
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
    int dataAddValue;
};



void* producer(void* argVoid) {
    auto arg = (GlobalArg*)argVoid;
    auto qProduct = arg->qProduct;
    auto sem = arg->sem;

    int i = 1;

    for (;; ++i) {
        sem->waitEmpty();

        qProduct->push(i + arg->dataAddValue);

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
    constexpr int NUM_PRODUCERS = 3;
    constexpr int NUM_CONSUMERS = 2;

    GlobalSemaphore sem;
    queue<int> qProduct;

    pthread_t lstTidProducer[NUM_PRODUCERS];
    pthread_t lstTidConsumer[NUM_CONSUMERS];

    int ret = 0;


    sem.init(0, 6);


    // PREPARE ARGUMENTS
    GlobalArg argPro[NUM_PRODUCERS];
    GlobalArg argCon;

    for (int i = 0; i < NUM_PRODUCERS; ++i) {
        argPro[i].qProduct = &qProduct;
        argPro[i].sem = &sem;
        argPro[i].dataAddValue = i * 1000;
    }

    argCon.qProduct = &qProduct;
    argCon.sem = &sem;


    // CREATE THREADS
    for (int i = 0; i < NUM_PRODUCERS; ++i) {
        ret = pthread_create(&lstTidProducer[i], nullptr, producer, &argPro[i]);
    }

    for (int i = 0; i < NUM_CONSUMERS; ++i) {
        ret = pthread_create(&lstTidConsumer[i], nullptr, consumer, &argCon);
    }


    // JOIN THREADS
    for (int i = 0; i < NUM_PRODUCERS; ++i) {
        ret = pthread_join(lstTidProducer[i], nullptr);
    }

    for (int i = 0; i < NUM_CONSUMERS; ++i) {
        ret = pthread_join(lstTidConsumer[i], nullptr);
    }


    sem.destroy();


    return 0;
}
