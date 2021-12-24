/*
THE PRODUCER-CONSUMER PROBLEM

SOLUTION TYPE B: USING SEMAPHORE
    Version B03: 2 fast producers, 1 slow consumer
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
    int startValue
) {
    int i = 1;

    for (;; ++i) {
        semEmpty->acquire();

        qProduct->push(i + startValue);

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
    TypeSemaphore semEmpty(1);  // remaining space in queue

    queue<int> qProduct;


    auto thProducerA = std::thread(producer, &semFill, &semEmpty, &qProduct, 0);
    auto thProducerB = std::thread(producer, &semFill, &semEmpty, &qProduct, 1000);
    auto thConsumer = std::thread(consumer, &semFill, &semEmpty, &qProduct);


    thProducerA.join();
    thProducerB.join();
    thConsumer.join();


    return 0;
}
