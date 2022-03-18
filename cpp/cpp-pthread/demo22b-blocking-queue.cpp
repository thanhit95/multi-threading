/*
BLOCKING QUEUES
Version B: A fast producer and a slow consumer

Blocking queues in C++ POSIX threading are not supported by default.
So, I use mylib::BlockingQueue for this demonstration.
*/


#include <iostream>
#include <string>
#include <unistd.h>
#include <pthread.h>
#include "mylib-blockingqueue.hpp"
using namespace std;
using namespace mylib;



void* producer(void* arg) {
    auto blkQueue = (BlockingQueue<string>*) arg;

    blkQueue->put("Alice");
    blkQueue->put("likes");

    /*
    Due to reaching the maximum capacity = 2, when executing blkQueue->put("singing"),
    this thread is going to sleep until the queue removes an element.
    */

    blkQueue->put("singing");

    pthread_exit(nullptr);
    return nullptr;
}



void* consumer(void* arg) {
    auto blkQueue = (BlockingQueue<string>*) arg;
    string data;

    sleep(2);

    for (int i = 0; i < 3; ++i) {
        cout << "\nWaiting for data..." << endl;
        data = blkQueue->take();
        cout << "    " << data << endl;
    }

    pthread_exit(nullptr);
    return nullptr;
}



int main() {
    pthread_t tidProducer, tidConsumer;
    auto blkQueue = BlockingQueue<string>(); // blocking queue with capacity = 2

    int ret = 0;

    ret = pthread_create(&tidProducer, nullptr, &producer, &blkQueue);
    ret = pthread_create(&tidConsumer, nullptr, &consumer, &blkQueue);

    ret = pthread_join(tidProducer, nullptr);
    ret = pthread_join(tidConsumer, nullptr);

    return 0;
}
