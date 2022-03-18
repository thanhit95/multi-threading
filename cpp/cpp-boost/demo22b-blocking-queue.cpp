/*
BLOCKING QUEUES
Version B: A fast producer and a slow consumer

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
    blkQueue->put("Alice");
    blkQueue->put("likes");

    /*
    Due to reaching the maximum capacity = 2, when executing blkQueue->put("singing"),
    this thread is going to sleep until the queue removes an element.
    */

    blkQueue->put("singing");
}



void consumer(BlockingQueue<string>* blkQueue) {
    string data;
    boost::this_thread::sleep_for(boost::chrono::seconds(2));

    for (int i = 0; i < 3; ++i) {
        cout << "\nWaiting for data..." << endl;
        data = blkQueue->take();
        cout << "    " << data << endl;
    }
}



int main() {
    BlockingQueue<string> blkQueue(2); // blocking queue with capacity = 2

    boost::thread thProducer(&producer, &blkQueue);
    boost::thread thConsumer(&consumer, &blkQueue);

    thProducer.join();
    thConsumer.join();

    return 0;
}
