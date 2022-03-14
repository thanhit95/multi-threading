/*
THE PRODUCER-CONSUMER PROBLEM

SOLUTION TYPE A: USING BLOCKING QUEUES
    Version A04: Multiple fast producers, multiple slow consumers
*/


#include <iostream>
#include <boost/chrono.hpp>
#include <boost/thread.hpp>
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
        boost::this_thread::sleep_for(boost::chrono::seconds(1));
    }
}



int main() {
    BlockingQueue<int> blkq;


    const int NUM_PRODUCERS = 3;
    const int NUM_CONSUMERS = 2;

    boost::thread_group lstThProducer;
    boost::thread_group lstThConsumer;


    // CREATE THREADS
    for (int i = 0; i < NUM_PRODUCERS; ++i) {
        lstThProducer.add_thread(new boost::thread(producer, &blkq, i * 1000));
    }

    for (int i = 0; i < NUM_CONSUMERS; ++i) {
        lstThConsumer.add_thread(new boost::thread(consumer, &blkq));
    }


    // JOIN THREADS
    lstThProducer.join_all();
    lstThConsumer.join_all();


    return 0;
}
