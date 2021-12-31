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



void producer(BlockingQueue<int>* qProduct) {
    int i = 1;

    for (;; ++i) {
        qProduct->put(i);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}



void consumer(BlockingQueue<int>* qProduct) {
    int data = 0;

    for (;;) {
        data = qProduct->take();
        cout << "Consumer " << data << endl;
    }
}



int main() {
    auto qProduct = BlockingQueue<int>();

    auto thProducer = std::thread(producer, &qProduct);
    auto thConsumer = std::thread(consumer, &qProduct);

    thProducer.join();
    thConsumer.join();

    return 0;
}
