/*
THE PRODUCER-CONSUMER PROBLEM

SOLUTION TYPE A: USING BLOCKING QUEUES
    Version A04: Multiple fast producers, multiple slow consumers
*/


#include <iostream>
#include <thread>
#include <chrono>
#include "mylib-blockingqueue.hpp"
using namespace std;
using namespace mylib;



struct ProducerArg {
    BlockingQueue<int>* blkq;
    int startValue;
};



void* producer(void* argVoid) {
    auto arg = (ProducerArg*) argVoid;
    int i = 1;

    for (;; ++i) {
        arg->blkq->put(i + arg->startValue);
    }

    pthread_exit(nullptr);
    return nullptr;
}



void* consumer(void* arg) {
    auto blkq = (BlockingQueue<int>*) arg;
    int data = 0;

    for (;;) {
        data = blkq->take();
        cout << "Consumer " << data << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    pthread_exit(nullptr);
    return nullptr;
}



int main() {
    auto blkq = BlockingQueue<int>(5);

    constexpr int NUM_PRODUCERS = 3;
    constexpr int NUM_CONSUMERS = 2;

    pthread_t lstTidProducer[NUM_PRODUCERS];
    pthread_t lstTidConsumer[NUM_CONSUMERS];
    ProducerArg lstArgPro[NUM_PRODUCERS];

    int ret = 0;


    // PREPARE ARGUMENTS
    for (int i = 0; i < NUM_PRODUCERS; ++i) {
        lstArgPro[i] = { &blkq, i * 1000 };
    }


    // CREATE THREADS
    for (int i = 0; i < NUM_PRODUCERS; ++i) {
        ret = pthread_create(&lstTidProducer[i], nullptr, producer, &lstArgPro[i]);
    }

    for (int i = 0; i < NUM_CONSUMERS; ++i) {
        ret = pthread_create(&lstTidConsumer[i], nullptr, consumer, &blkq);
    }


    // JOIN THREADS
    for (int i = 0; i < NUM_PRODUCERS; ++i) {
        ret = pthread_join(lstTidProducer[i], nullptr);
    }

    for (int i = 0; i < NUM_CONSUMERS; ++i) {
        ret = pthread_join(lstTidConsumer[i], nullptr);
    }


    return 0;
}
