/*
THE PRODUCER-CONSUMER PROBLEM


PROBLEM STATEMENT
    The producer–consumer problem (also known as the bounded-buffer problem)
    is a classic example of a multi-process synchronization problem.
    The first version of which was proposed by Edsger W. Dijkstra in 1965.

    In the producer-consumer problem, there is one producer that is producing something
    and there is one consumer that is consuming the products produced by the producer.
    The producers and consumers share the same memory buffer that is of fixed-size.

    The job of the producer is to generate the data, put it into the buffer, and again start
    generating data. While the job of the consumer is to consume the data from the buffer.

    In the later formulation of the problem, Dijkstra proposed
    multiple producers and consumers sharing a finite collection of buffers.

    What's the problem here?
    - The producer should produce data only when the buffer is not full.
    If the buffer is full, then the producer shouldn't be allowed to put any data into the buffer.
    - The consumer should consume data only when the buffer is not empty.
    If the buffer is empty, then the consumer shouldn't be allowed to take any data from the buffer.
    - The producer and consumer should not access the buffer at the same time.


SOLUTION TYPE A - USING BLOCKING QUEUE
    version a01: 1 slow producer, 1 fast consumer
*/


#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include "extool-blocking-collection.hpp"

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
    pthread_t tidProduder, tidConsumer;
    BlockingQueue<int> qProduct;

    int ret = 0;

    ret = pthread_create(&tidProduder, nullptr, producer, (void*)&qProduct);
    ret = pthread_create(&tidConsumer, nullptr, consumer, (void*)&qProduct);

    ret = pthread_join(tidProduder, nullptr);
    ret = pthread_join(tidConsumer, nullptr);

    return 0;
}
