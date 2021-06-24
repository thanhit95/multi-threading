/*
THE PRODUCER-CONSUMER PROBLEM

SOLUTION TYPE A - USING BLOCKING QUEUE
    Version A03: 1 slow producers, 2 fast consumer
*/


#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include "extool-blocking-collection.hpp"
using namespace std;
using namespace code_machina;



void producer(BlockingQueue<int>* qProduct) {
    int i = 1;

    for (;; ++i) {
        qProduct->add(i);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}



void consumer(string name, BlockingQueue<int>* qProduct) {
    int data = 0;
    BlockingCollectionStatus status;

    for (;;) {
        status = qProduct->take(data);

        if (BlockingCollectionStatus::Ok == status) {
            cout << "Consumer " << name << ": " << data << endl;
        }
        else {
            cerr << "Consumer error" << endl;
        }
    }
}



int main() {
    BlockingQueue<int> qProduct;

    auto thProducer = std::thread(producer, &qProduct);
    auto thConsumerFoo = std::thread(consumer, "foo", &qProduct);
    auto thConsumerBar = std::thread(consumer, "bar", &qProduct);

    thProducer.join();
    thConsumerFoo.join();
    thConsumerBar.join();

    return 0;
}
