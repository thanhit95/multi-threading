/*
THE PRODUCER-CONSUMER PROBLEM

SOLUTION TYPE A - USING BLOCKING QUEUE
    Version A01: 1 slow producer, 1 fast consumer
*/


#include <iostream>
#include <thread>
#include <chrono>
#include "extool-blocking-collection.hpp"
using namespace std;
using namespace code_machina;



void producer(BlockingQueue<int> *qProduct) {
    int i = 1;

    for (;; ++i) {
        qProduct->add(i);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}



void consumer(BlockingQueue<int> *qProduct) {
    int data;
    BlockingCollectionStatus status;

    for (;;) {
        status = qProduct->take(data);

        if (BlockingCollectionStatus::Ok == status) {
            cout << "Consumer " << data << endl;
        }
        else {
            cerr << "Consumer error" << endl;
        }
    }
}



int main() {
    BlockingQueue<int> qProduct;

    auto thProducer = std::thread(producer, &qProduct);
    auto thConsumer = std::thread(consumer, &qProduct);

    thProducer.join();
    thConsumer.join();

    return 0;
}
