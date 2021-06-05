/*
THE PRODUCER-CONSUMER PROBLEM

SOLUTION TYPE A - USING BLOCKING QUEUE
    version a03: 1 slow producers, 2 fast consumer
*/


#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include "BlockingCollection.hpp"

using namespace std;
using namespace code_machina;



struct ConsumerArg {
    BlockingQueue<int> *pqProduct;
    int idCon;
};



void* producer(void *arg) {
    auto pqProduct = (BlockingQueue<int>*)arg;

    int i = 1;

    for (;; ++i) {
        pqProduct->add(i);
        sleep(1);
    }

    pthread_exit(nullptr);
    return (void*)0;
}



void *consumer(void *argVoid) {
    auto arg = (ConsumerArg*)argVoid;
    auto pqProduct = arg->pqProduct;

    int data;
    BlockingCollectionStatus status;

    for (;;) {
        status = pqProduct->take(data);

        if (status == BlockingCollectionStatus::Ok) {
            cout << "consumer" << arg->idCon << " " << data << endl;
        }
        else {
            cerr << "consumer error" << endl;
        }
    }

    pthread_exit(nullptr);
    return (void*)0;
}



int main() {
    pthread_t pidProduder;
    pthread_t pidConsumer[2];
    BlockingQueue<int> qProduct;

    int ret = 0;

    ConsumerArg conArg0, conArg1;
    conArg0.pqProduct = conArg1.pqProduct = &qProduct;
    conArg0.idCon = 0;
    conArg1.idCon = 1;

    ret = pthread_create(&pidProduder, nullptr, producer, (void*)&qProduct);
    ret = pthread_create(&pidConsumer[0], nullptr, consumer, (void*)&conArg0);
    ret = pthread_create(&pidConsumer[1], nullptr, consumer, (void*)&conArg1);

    ret = pthread_join(pidProduder, nullptr);
    ret = pthread_join(pidConsumer[0], nullptr);
    ret = pthread_join(pidConsumer[1], nullptr);

    return 0;
}
