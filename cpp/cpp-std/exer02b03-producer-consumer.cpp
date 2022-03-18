/*
THE PRODUCER-CONSUMER PROBLEM

SOLUTION TYPE B: USING SEMAPHORES
    Version B03: 2 fast producers, 1 slow consumer
*/


#include <iostream>
#include <queue>
#include <chrono>
#include <thread>
#include <semaphore>
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

    auto thProducerA = std::thread(&producer, &semFill, &semEmpty, &q, 0);
    auto thProducerB = std::thread(&producer, &semFill, &semEmpty, &q, 1000);
    auto thConsumer = std::thread(&consumer, &semFill, &semEmpty, &q);

    thProducerA.join();
    thProducerB.join();
    thConsumer.join();

    return 0;
}
