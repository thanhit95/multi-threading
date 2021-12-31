/*
THE PRODUCER-CONSUMER PROBLEM

SOLUTION TYPE A: USING BLOCKING QUEUES
    Version A03: 1 slow producer, 2 fast consumers
*/


#include <iostream>
#include <string>
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



void consumer(string name, BlockingQueue<int>* qProduct) {
    int data = 0;

    for (;;) {
        data = qProduct->take();
        cout << "Consumer " << name << ": " << data << endl;
    }
}



int main() {
    auto qProduct = BlockingQueue<int>();

    auto thProducer = std::thread(producer, &qProduct);
    auto thConsumerFoo = std::thread(consumer, "foo", &qProduct);
    auto thConsumerBar = std::thread(consumer, "bar", &qProduct);

    thProducer.join();
    thConsumerFoo.join();
    thConsumerBar.join();

    return 0;
}
