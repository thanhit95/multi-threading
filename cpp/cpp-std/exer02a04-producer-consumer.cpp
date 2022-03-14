/*
THE PRODUCER-CONSUMER PROBLEM

SOLUTION TYPE A: USING BLOCKING QUEUES
    Version A04: Multiple fast producers, multiple slow consumers
*/


#include <iostream>
#include <chrono>
#include <thread>
#include "mylib-blockingqueue.hpp"
using namespace std;
using namespace mylib;



void producer(BlockingQueue<int>* blkq, int startValue) {
    int i = 1;

    for (;; ++i) {
        blkq->put(i + startValue);
    }
}



void consumer(BlockingQueue<int>* blkq) {
    int data = 0;

    for (;;) {
        data = blkq->take();
        cout << "Consumer " << data << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}



int main() {
    auto blkq = BlockingQueue<int>();


    constexpr int NUM_PRODUCERS = 3;
    constexpr int NUM_CONSUMERS = 2;

    std::thread lstThProducer[NUM_PRODUCERS];
    std::thread lstThConsumer[NUM_CONSUMERS];


    // CREATE THREADS
    for (int i = 0; i < NUM_PRODUCERS; ++i) {
        lstThProducer[i] = std::thread(producer, &blkq, i * 1000);
    }

    for (auto&& th : lstThConsumer) {
        th = std::thread(consumer, &blkq);
    }


    // JOIN THREADS
    for (auto&& th : lstThProducer) {
        th.join();
    }

    for (auto&& th : lstThConsumer) {
        th.join();
    }


    return 0;
}
