/*
THE PRODUCER-CONSUMER PROBLEM

SOLUTION TYPE B: USING SEMAPHORES
    Version B01: 1 slow producer, 1 fast consumer
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
    queue<int>* q
) {
    int i = 1;

    for (;; ++i) {
        semEmpty->acquire();

        q->push(i);
        boost::this_thread::sleep_for(boost::chrono::seconds(1));

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

        semEmpty->release();
    }
}



int main() {
    mylib::Semaphore semFill(0);   // item produced
    mylib::Semaphore semEmpty(1);  // remaining space in queue

    queue<int> q;

    boost::thread thProducer(producer, &semFill, &semEmpty, &q);
    boost::thread thConsumer(consumer, &semFill, &semEmpty, &q);

    thProducer.join();
    thConsumer.join();

    return 0;
}
