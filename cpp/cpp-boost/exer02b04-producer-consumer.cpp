/*
THE PRODUCER-CONSUMER PROBLEM

SOLUTION TYPE B: USING SEMAPHORES
    Version B04: Multiple fast producers, multiple slow consumers
*/


#include <iostream>
#include <queue>
#include <boost/chrono.hpp>
#include <boost/thread.hpp>
#include "mylib-semaphore.hpp"
using namespace std;



void producer(
    mylib::Semaphore* semFill,
    mylib::Semaphore* semEmpty,
    queue<int>* q,
    int startValue
) {
    int i = 1;

    for (;; ++i) {
        semEmpty->acquire();
        q->push(i + startValue);
        semFill->release();
    }
}



void consumer(
    mylib::Semaphore* semFill,
    mylib::Semaphore* semEmpty,
    queue<int>* q
) {
    int data = 0;

    for (;;) {
        semFill->acquire();

        data = q->front();
        q->pop();

        cout << "Consumer " << data << endl;
        boost::this_thread::sleep_for(boost::chrono::seconds(1));

        semEmpty->release();
    }
}



int main() {
    mylib::Semaphore semFill(0);   // item produced
    mylib::Semaphore semEmpty(1);  // remaining space in queue

    queue<int> q;


    const int NUM_PRODUCERS = 3;
    const int NUM_CONSUMERS = 2;

    boost::thread_group lstThProducer;
    boost::thread_group lstThConsumer;


    // CREATE THREADS
    for (int i = 0; i < NUM_PRODUCERS; ++i) {
        lstThProducer.add_thread(new boost::thread(
            &producer, &semFill, &semEmpty, &q, i * 1000
        ));
    }

    for (int i = 0; i < NUM_CONSUMERS; ++i) {
        lstThConsumer.add_thread(new boost::thread(
            &consumer, &semFill, &semEmpty, &q
        ));
    }


    // JOIN THREADS
    lstThProducer.join_all();
    lstThConsumer.join_all();


    return 0;
}
