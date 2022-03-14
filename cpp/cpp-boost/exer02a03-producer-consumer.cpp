/*
THE PRODUCER-CONSUMER PROBLEM

SOLUTION TYPE A: USING BLOCKING QUEUES
    Version A03: 1 slow producer, 2 fast consumers
*/


#include <iostream>
#include <string>
#include <boost/chrono.hpp>
#include <boost/thread.hpp>
#include "mylib-blockingqueue.hpp"
using namespace std;
using namespace mylib;



void producer(BlockingQueue<int>* blkq) {
    int i = 1;

    for (;; ++i) {
        blkq->put(i);
        boost::this_thread::sleep_for(boost::chrono::seconds(1));
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
    BlockingQueue<int> blkq;

    boost::thread thProducer(producer, &blkq);
    boost::thread thConsumerFoo(consumer, "foo", &blkq);
    boost::thread thConsumerBar(consumer, "bar", &blkq);

    thProducer.join();
    thConsumerFoo.join();
    thConsumerBar.join();

    return 0;
}
