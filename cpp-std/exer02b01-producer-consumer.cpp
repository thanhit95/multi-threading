/*
THE PRODUCER-CONSUMER PROBLEM

SOLUTION TYPE B: USING SEMAPHORES
    Version B01: 1 slow producer, 1 fast consumer
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
    queue<int>* qProduct
) {
    int i = 1;

    for (;; ++i) {
        semEmpty->acquire();

        qProduct->push(i);
        std::this_thread::sleep_for(std::chrono::seconds(1));

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

        semEmpty->release();
    }
}



int main() {
    TypeSemaphore semFill(0);   // item produced
    TypeSemaphore semEmpty(1);  // remaining space in queue

    queue<int> qProduct;


    auto thProducer = std::thread(producer, &semFill, &semEmpty, &qProduct);
    auto thConsumer = std::thread(consumer, &semFill, &semEmpty, &qProduct);


    thProducer.join();
    thConsumer.join();


    return 0;
}
