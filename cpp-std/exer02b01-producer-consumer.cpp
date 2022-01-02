/*
THE PRODUCER-CONSUMER PROBLEM

SOLUTION TYPE B: USING SEMAPHORES
    Version B01: 1 slow producer, 1 fast consumer
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
    queue<int>* q
) {
    int i = 1;

    for (;; ++i) {
        semEmpty->acquire();

        q->push(i);
        std::this_thread::sleep_for(std::chrono::seconds(1));

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

        semEmpty->release();
    }
}



int main() {
    cntsemaphore semFill(0);   // item produced
    cntsemaphore semEmpty(1);  // remaining space in queue

    queue<int> q;


    auto thProducer = std::thread(producer, &semFill, &semEmpty, &q);
    auto thConsumer = std::thread(consumer, &semFill, &semEmpty, &q);


    thProducer.join();
    thConsumer.join();


    return 0;
}
