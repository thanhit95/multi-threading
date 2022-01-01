/*
THE PRODUCER-CONSUMER PROBLEM

SOLUTION TYPE A: USING BLOCKING QUEUES
    Version A01: 1 slow producer, 1 fast consumer
*/


#include <iostream>
#include <thread>
#include <chrono>
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

    auto thProducer = std::thread(producer, &blkq);
    auto thConsumer = std::thread(consumer, &blkq);

    thProducer.join();
    thConsumer.join();

    return 0;
}
