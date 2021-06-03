/*
PRODUCER - CONSUMER PROBLEM

SOLUTION TYPE A - USING BLOCKING QUEUE
    version a01: 1 slow producer, 1 fast consumer
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



void *consumer(void *arg) {
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
    pthread_t pidProduder, pidConsumer;
    BlockingQueue<int> qProduct;

    int ret = 0;

    ret = pthread_create(&pidProduder, nullptr, producer, (void*)&qProduct);
    ret = pthread_create(&pidConsumer, nullptr, consumer, (void*)&qProduct);

    pthread_join(pidProduder, nullptr);
    pthread_join(pidConsumer, nullptr);

    return 0;
}
