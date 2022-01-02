/*
THE PRODUCER-CONSUMER PROBLEM

SOLUTION TYPE A: USING BLOCKING QUEUES
    Version A03: 1 slow producer, 2 fast consumers
*/


#include <iostream>
#include <string>
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



void consumer(string name, BlockingQueue<int>* blkq) {
    int data = 0;

    for (;;) {
        data = blkq->take();
        cout << "Consumer " << name << ": " << data << endl;
    }
}



int main() {
    auto blkq = BlockingQueue<int>();

    auto thProducer = std::thread(producer, &blkq);
    auto thConsumerFoo = std::thread(consumer, "foo", &blkq);
    auto thConsumerBar = std::thread(consumer, "bar", &blkq);

    thProducer.join();
    thConsumerFoo.join();
    thConsumerBar.join();

    return 0;
}
