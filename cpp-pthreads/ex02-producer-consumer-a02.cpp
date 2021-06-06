/*
THE PRODUCER-CONSUMER PROBLEM

SOLUTION TYPE A - USING BLOCKING QUEUE
    version a02: 2 slow producers, 1 fast consumer
*/


#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include "BlockingCollection.hpp"

using namespace std;
using namespace code_machina;



void* producer(void *arg) {
    auto pqProduct = (BlockingQueue<int>*)arg;

    int i = 1;

    for (;; ++i) {
        pqProduct->add(i);
        sleep(1);
    }

    pthread_exit(nullptr);
    return (void*)0;
}



void* consumer(void *arg) {
    auto pqProduct = (BlockingQueue<int>*)arg;

    int data;
    BlockingCollectionStatus status;

    for (;;) {
        status = pqProduct->take(data);

        if (status == BlockingCollectionStatus::Ok) {
            cout << "consumer " << data << endl;
        }
        else {
            cerr << "consumer error" << endl;
        }
    }

    pthread_exit(nullptr);
    return (void*)0;
}



int main() {
    pthread_t tidProduder[2];
    pthread_t tidConsumer;
    BlockingQueue<int> qProduct;

    int ret = 0;

    ret = pthread_create(&tidProduder[0], nullptr, producer, (void*)&qProduct);
    ret = pthread_create(&tidProduder[1], nullptr, producer, (void*)&qProduct);
    ret = pthread_create(&tidConsumer, nullptr, consumer, (void*)&qProduct);

    ret = pthread_join(tidProduder[0], nullptr);
    ret = pthread_join(tidProduder[1], nullptr);
    ret = pthread_join(tidConsumer, nullptr);

    return 0;
}
