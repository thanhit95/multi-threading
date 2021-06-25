/*
THE PRODUCER-CONSUMER PROBLEM

SOLUTION TYPE B: USING SEMAPHORE
    Version B04: Multiple fast producers, multiple slow consumers
*/


#include <iostream>
#include <queue>
#include <thread>
#include <semaphore>
#include <chrono>
using namespace std;



using TypeSemaphore = std::counting_semaphore<>;



void producer(
    TypeSemaphore* semFill,
    TypeSemaphore* semEmpty,
    queue<int>* qProduct,
    int dataAddValue
) {
    int i = 1;

    for (;; ++i) {
        semEmpty->acquire();

        qProduct->push(i + dataAddValue);

        semFill->release();
    }
}



void consumer(
    TypeSemaphore* semFill,
    TypeSemaphore* semEmpty,
    queue<int>* qProduct
) {
    int data = 0;

    for (;;) {
        semFill->acquire();

        data = qProduct->front();
        qProduct->pop();

        cout << "Consumer " << data << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));

        semEmpty->release();
    }
}



int main() {
    TypeSemaphore semFill(0);   // item produced
    TypeSemaphore semEmpty(6);  // remaining space in queue

    queue<int> qProduct;


    constexpr int NUM_PRODUCERS = 3;
    constexpr int NUM_CONSUMERS = 2;

    std::thread lstThProducer[NUM_PRODUCERS];
    std::thread lstThConsumer[NUM_CONSUMERS];


    // CREATE THREADS
    for (int i = 0; i < NUM_PRODUCERS; ++i) {
        lstThProducer[i] = std::thread(producer, &semFill, &semEmpty, &qProduct, i * 1000);
    }

    for (auto&& th : lstThConsumer) {
        th = std::thread(consumer, &semFill, &semEmpty, &qProduct);
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
