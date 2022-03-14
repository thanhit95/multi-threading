/*
BLOCKING QUEUES
Version A: A slow producer and a fast consumer

Blocking queues in C++ Boost threading are not supported by default.
So, I use mylib::BlockingQueue for this demonstration.
*/


#include <iostream>
#include <string>
#include <boost/chrono.hpp>
#include <boost/thread.hpp>
#include "mylib-blockingqueue.hpp"
using namespace std;
using namespace mylib;



void producer(BlockingQueue<string>* blkQueue) {
    boost::this_thread::sleep_for(boost::chrono::seconds(2));
    blkQueue->put("Alice");

    boost::this_thread::sleep_for(boost::chrono::seconds(2));
    blkQueue->put("likes");

    boost::this_thread::sleep_for(boost::chrono::seconds(2));
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
    BlockingQueue<string> blkQueue;

    boost::thread thProducer(producer, &blkQueue);
    boost::thread thConsumer(consumer, &blkQueue);

    thProducer.join();
    thConsumer.join();

    return 0;
}
