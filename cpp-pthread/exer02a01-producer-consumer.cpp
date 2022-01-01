/*
THE PRODUCER-CONSUMER PROBLEM

SOLUTION TYPE A: USING BLOCKING QUEUES
    Version A01: 1 slow producer, 1 fast consumer
*/


#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include "../cpp-std/mylib-blockingqueue.hpp"
using namespace std;
using namespace mylib;



void* producer(void* arg) {
    auto blkq = (BlockingQueue<int>*) arg;

    int i = 1;

    for (;; ++i) {
        blkq->put(i);
        sleep(1);
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
    }

    pthread_exit(nullptr);
    return nullptr;
}



int main() {
    pthread_t tidProducer, tidConsumer;
    BlockingQueue<int> blkq;

    int ret = 0;

    ret = pthread_create(&tidProducer, nullptr, producer, &blkq);
    ret = pthread_create(&tidConsumer, nullptr, consumer, &blkq);

    ret = pthread_join(tidProducer, nullptr);
    ret = pthread_join(tidConsumer, nullptr);

    return 0;
}
