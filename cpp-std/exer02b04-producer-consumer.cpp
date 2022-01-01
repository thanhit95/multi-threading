/*
THE PRODUCER-CONSUMER PROBLEM

SOLUTION TYPE B: USING SEMAPHORES
    Version B04: Multiple fast producers, multiple slow consumers
*/


#include <iostream>
#include <queue>
#include <thread>
#include <semaphore>
#include <chrono>
using namespace std;



using cntsemaphore = std::counting_semaphore<>;



void producer(
    cntsemaphore* semFill,
    cntsemaphore* semEmpty,
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
    cntsemaphore* semFill,
    cntsemaphore* semEmpty,
    queue<int>* q
) {
    int data = 0;

    for (;;) {
        semFill->acquire();

        data = q->front();
        q->pop();

        cout << "Consumer " << data << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));

        semEmpty->release();
    }
}



int main() {
    cntsemaphore semFill(0);   // item produced
    cntsemaphore semEmpty(1);  // remaining space in queue

    queue<int> q;


    constexpr int NUM_PRODUCERS = 3;
    constexpr int NUM_CONSUMERS = 2;

    std::thread lstThProducer[NUM_PRODUCERS];
    std::thread lstThConsumer[NUM_CONSUMERS];


    // CREATE THREADS
    for (int i = 0; i < NUM_PRODUCERS; ++i) {
        lstThProducer[i] = std::thread(producer, &semFill, &semEmpty, &q, i * 1000);
    }

    for (auto&& th : lstThConsumer) {
        th = std::thread(consumer, &semFill, &semEmpty, &q);
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
