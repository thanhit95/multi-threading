/*
THE PRODUCER-CONSUMER PROBLEM

SOLUTION TYPE B: USING SEMAPHORES
    Version B03: 2 fast producers, 1 slow consumer
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

    boost::thread thProducerA(producer, &semFill, &semEmpty, &q, 0);
    boost::thread thProducerB(producer, &semFill, &semEmpty, &q, 1000);
    boost::thread thConsumer(consumer, &semFill, &semEmpty, &q);

    thProducerA.join();
    thProducerB.join();
    thConsumer.join();

    return 0;
}
