/*
THE PRODUCER-CONSUMER PROBLEM

SOLUTION TYPE A: USING BLOCKING QUEUE
    Version A03: 1 slow producers, 2 fast consumer
*/


#include <iostream>
#include <string>
#include <pthread.h>
#include <unistd.h>
#include "extool-blocking-collection.hpp"
using namespace std;
using namespace code_machina;



struct ConsumerArg {
    string name;
    BlockingQueue<int> *qProduct;
};



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



void* consumer(void* argVoid) {
    auto arg = (ConsumerArg*)argVoid;
    auto qProduct = arg->qProduct;

    int data;
    BlockingCollectionStatus status;

    for (;;) {
        status = qProduct->take(data);

        if (BlockingCollectionStatus::Ok == status) {
            cout << "Consumer " << arg->name << ": " << data << endl;
        }
        else {
            cerr << "Consumer error" << endl;
        }
    }

    pthread_exit(nullptr);
    return nullptr;
}



int main() {
    pthread_t tidProducer;
    pthread_t tidConsumerFoo, tidConsumerBar;
    BlockingQueue<int> qProduct;

    int ret = 0;

    ConsumerArg argFoo = { "foo", &qProduct };
    ConsumerArg argBar = { "bar", &qProduct };

    ret = pthread_create(&tidProducer, nullptr, producer, &qProduct);
    ret = pthread_create(&tidConsumerFoo, nullptr, consumer, &argFoo);
    ret = pthread_create(&tidConsumerBar, nullptr, consumer, &argBar);

    ret = pthread_join(tidProducer, nullptr);
    ret = pthread_join(tidConsumerFoo, nullptr);
    ret = pthread_join(tidConsumerBar, nullptr);

    return 0;
}
