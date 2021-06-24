/*
THE PRODUCER-CONSUMER PROBLEM

SOLUTION TYPE A - USING BLOCKING QUEUE
    Version A02: 2 slow producers, 1 fast consumer
*/


#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include "extool-blocking-collection.hpp"
using namespace std;
using namespace code_machina;



void* producer(void* arg) {
    auto qProduct = (BlockingQueue<int>*)arg;

    int i = 1;

    for (;; ++i) {
        qProduct->add(i);
        sleep(1);
    }

    pthread_exit(nullptr);
    return nullptr;
}



void* consumer(void* arg) {
    auto qProduct = (BlockingQueue<int>*)arg;

    int data;
    BlockingCollectionStatus status;

    for (;;) {
        status = qProduct->take(data);

        if (BlockingCollectionStatus::Ok == status) {
            cout << "Consumer " << data << endl;
        }
        else {
            cerr << "Consumer error" << endl;
        }
    }

    pthread_exit(nullptr);
    return nullptr;
}



int main() {
    pthread_t tidProducerA, tidProducerB;
    pthread_t tidConsumer;
    BlockingQueue<int> qProduct;

    int ret = 0;

    ret = pthread_create(&tidProducerA, nullptr, producer, &qProduct);
    ret = pthread_create(&tidProducerB, nullptr, producer, &qProduct);
    ret = pthread_create(&tidConsumer, nullptr, consumer, &qProduct);

    ret = pthread_join(tidProducerA, nullptr);
    ret = pthread_join(tidProducerB, nullptr);
    ret = pthread_join(tidConsumer, nullptr);

    return 0;
}
