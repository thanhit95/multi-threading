/*
BLOCKING QUEUES
Version A: A slow producer and a fast consumer

Blocking queues in C++ std threading are not supported by default.
So, I use mylib::BlockingQueue for this demonstration.
*/


#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include "mylib-blockingqueue.hpp"
using namespace std;
using namespace mylib;



void producer(BlockingQueue<string>* blkQueue) {
    std::this_thread::sleep_for(std::chrono::seconds(2));
    blkQueue->put("Alice");

    std::this_thread::sleep_for(std::chrono::seconds(2));
    blkQueue->put("likes");

    std::this_thread::sleep_for(std::chrono::seconds(2));
    blkQueue->put("singing");
}



void consumer(BlockingQueue<string>* blkQueue) {
    string data;

    for (int i = 0; i < 3; ++i) {
        cout << "\nWaiting for data..." << endl;
        data = blkQueue->take();
        cout << "    " << data << endl;
    }
}



int main() {
    auto blkQueue = BlockingQueue<string>();

    auto thProducer = std::thread(producer, &blkQueue);
    auto thConsumer = std::thread(consumer, &blkQueue);

    thProducer.join();
    thConsumer.join();

    return 0;
}
