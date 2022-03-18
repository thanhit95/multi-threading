/*
THE PRODUCER-CONSUMER PROBLEM

SOLUTION TYPE A: USING BLOCKING QUEUES
    Version A02: 2 slow producers, 1 fast consumer
*/


#include <iostream>
#include <chrono>
#include <thread>
#include "mylib-blockingqueue.hpp"
using namespace std;
using namespace mylib;



void producer(BlockingQueue<int>* blkq) {
    int i = 1;

    for (;; ++i) {
        blkq->put(i);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}



void consumer(BlockingQueue<int>* blkq) {
    int data = 0;

    for (;;) {
        data = blkq->take();
        cout << "Consumer " << data << endl;
    }
}



int main() {
    auto blkq = BlockingQueue<int>();

    auto thProducerA = std::thread(&producer, &blkq);
    auto thProducerB = std::thread(&producer, &blkq);
    auto thConsumer = std::thread(&consumer, &blkq);

    thProducerA.join();
    thProducerB.join();
    thConsumer.join();

    return 0;
}
