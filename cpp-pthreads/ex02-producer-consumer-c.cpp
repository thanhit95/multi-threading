/*
THE PRODUCER-CONSUMER PROBLEM

SOLUTION TYPE C - USING MONITOR
    multi fast producers, multi slow consumers
*/


#include <iostream>
#include <queue>
#include <pthread.h>
#include <unistd.h>
#include "mytool-random.hpp"

using namespace std;



template <typename T>
class Monitor {
private:
    std::queue<T> *q = nullptr;
    int maxQueueSize = 0;
    pthread_cond_t condFull = PTHREAD_COND_INITIALIZER;
    pthread_cond_t condEmpty = PTHREAD_COND_INITIALIZER;
    pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;


public:
    Monitor() = default;
    Monitor(const Monitor &other) = delete;
    Monitor(const Monitor &&other) = delete;
    void operator=(const Monitor &other) = delete;
    void operator=(const Monitor &&other) = delete;


    void init(int maxQueueSize, std::queue<T> *q) {
        destroy();

        this->q = q;
        this->maxQueueSize = maxQueueSize;
        condFull = PTHREAD_COND_INITIALIZER;
        condEmpty = PTHREAD_COND_INITIALIZER;
        mut = PTHREAD_MUTEX_INITIALIZER;
    }


    void destroy() {
        q = nullptr;
        maxQueueSize = 0;
        pthread_cond_destroy(&condFull);
        pthread_cond_destroy(&condEmpty);
        pthread_mutex_destroy(&mut);
    }


    void add(const T &item) {
        pthread_mutex_lock(&mut);

        while (q->size() == maxQueueSize) {
            pthread_cond_wait(&condFull, &mut);
        }

        q->push(item);

        if (q->size() == 1) {
            pthread_cond_signal(&condEmpty);
        }

        pthread_mutex_unlock(&mut);
    }


    T remove() {
        pthread_mutex_lock(&mut);

        while (q->size() == 0) {
            pthread_cond_wait(&condEmpty, &mut);
        }

        T item = q->front();
        q->pop();

        if (q->size() == maxQueueSize - 1) {
            pthread_cond_signal(&condFull);
        }

        pthread_mutex_unlock(&mut);

        return item;
    }
};



template <typename T>
void* producer(void *argVoid) {
    Monitor<T> *monitor = (Monitor<T>*)argVoid;

    mytool::RandIntGenerator intGen(0, 9);
    int dataAddFactor = intGen.get() * 1000;

    int i = 1;

    for (;; ++i) {
        monitor->add(i + dataAddFactor);
    }

    pthread_exit(nullptr);
    return (void*)0;
}



template <typename T>
void* consumer(void *argVoid) {
    Monitor<T> *monitor = (Monitor<T>*)argVoid;

    int data;

    for (;;) {
        data = monitor->remove();
        cout << "consumer " << data << endl;
        sleep(1);
    }

    pthread_exit(nullptr);
    return (void*)0;
}



int main() {
    constexpr int NUM_PRODUCERS = 3;
    constexpr int NUM_CONSUMERS = 2;

    pthread_t tidProduder[NUM_PRODUCERS];
    pthread_t tidConsumer[NUM_CONSUMERS];

    Monitor<int> monitor;
    queue<int> qProduct;
    constexpr int MAX_QUEUE_SIZE = 6;

    int ret = 0;


    // PREPARE ARGUMENTS
    monitor.init(MAX_QUEUE_SIZE, &qProduct);


    // CREATE THREADS
    for (int i = 0; i < NUM_PRODUCERS; ++i) {
        ret = pthread_create(&tidProduder[i], nullptr, producer<int>, &monitor);
    }

    for (int i = 0; i < NUM_CONSUMERS; ++i) {
        ret = pthread_create(&tidConsumer[i], nullptr, consumer<int>, &monitor);
    }


    // JOIN THREADS
    for (int i = 0; i < NUM_PRODUCERS; ++i) {
        ret = pthread_join(tidProduder[i], nullptr);
    }

    for (int i = 0; i < NUM_CONSUMERS; ++i) {
        ret = pthread_join(tidConsumer[i], nullptr);
    }


    monitor.destroy();
    return 0;
}
