/*
BLOCKING QUEUES
Version A: A slow producer and a fast consumer

Blocking queues in C++ POSIX threading are not supported by default.
So, I use mylib::BlockingQueue for this demonstration.
*/


#include <iostream>
#include <string>
#include <unistd.h>
#include <pthread.h>
#include "../cpp-std/mylib-blockingqueue.hpp"
using namespace std;
using namespace mylib;



void* producer(void* arg) {
    auto blkQueue = (BlockingQueue<string>*) arg;

    sleep(2);
    blkQueue->put("Alice");

    sleep(2);
    blkQueue->put("likes");

    sleep(2);
    blkQueue->put("singing");

    pthread_exit(nullptr);
    return nullptr;
}



void* consumer(void* arg) {
    auto blkQueue = (BlockingQueue<string>*) arg;
    string data;

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
    auto blkQueue = BlockingQueue<string>();

    int ret = 0;

    ret = pthread_create(&tidProducer, nullptr, producer, &blkQueue);
    ret = pthread_create(&tidConsumer, nullptr, consumer, &blkQueue);

    ret = pthread_join(tidProducer, nullptr);
    ret = pthread_join(tidConsumer, nullptr);

    return 0;
}
