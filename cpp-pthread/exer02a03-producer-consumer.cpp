/*
THE PRODUCER-CONSUMER PROBLEM

SOLUTION TYPE A: USING BLOCKING QUEUES
    Version A03: 1 slow producer, 2 fast consumers
*/


#include <iostream>
#include <string>
#include <unistd.h>
#include <pthread.h>
#include "../cpp-std/mylib-blockingqueue.hpp"
using namespace std;
using namespace mylib;



struct ConsumerArg {
    string name;
    BlockingQueue<int> *blkq;
};



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



void* consumer(void* argVoid) {
    auto arg = (ConsumerArg*) argVoid;
    auto blkq = arg->blkq;

    int data = 0;

    for (;;) {
        data = blkq->take();
        cout << "Consumer " << arg->name << ": " << data << endl;
    }

    pthread_exit(nullptr);
    return nullptr;
}



int main() {
    pthread_t tidProducer;
    pthread_t tidConsumerFoo, tidConsumerBar;
    BlockingQueue<int> blkq;

    int ret = 0;

    ConsumerArg argFoo = { "foo", &blkq };
    ConsumerArg argBar = { "bar", &blkq };

    ret = pthread_create(&tidProducer, nullptr, producer, &blkq);
    ret = pthread_create(&tidConsumerFoo, nullptr, consumer, &argFoo);
    ret = pthread_create(&tidConsumerBar, nullptr, consumer, &argBar);

    ret = pthread_join(tidProducer, nullptr);
    ret = pthread_join(tidConsumerFoo, nullptr);
    ret = pthread_join(tidConsumerBar, nullptr);

    return 0;
}
