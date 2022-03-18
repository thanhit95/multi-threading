/*
THE PRODUCER-CONSUMER PROBLEM

SOLUTION TYPE A: USING BLOCKING QUEUES
    Version A02: 2 slow producers, 1 fast consumer
*/


#include <iostream>
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



void consumer(BlockingQueue<int>* blkq) {
    int data = 0;

    for (;;) {
        data = blkq->take();
        cout << "Consumer " << data << endl;
    }
}



int main() {
    BlockingQueue<int> blkq;

    boost::thread thProducerA(&producer, &blkq);
    boost::thread thProducerB(&producer, &blkq);
    boost::thread thConsumer(&consumer, &blkq);

    thProducerA.join();
    thProducerB.join();
    thConsumer.join();

    return 0;
}
