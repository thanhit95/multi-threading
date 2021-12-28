/*
THE PRODUCER-CONSUMER PROBLEM

SOLUTION TYPE C: USING CONDITION VARIABLES & MONITORS
    Multiple fast producers, multiple slow consumers
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
    std::queue<T>* q = nullptr;
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


    void init(int maxQueueSize, std::queue<T>* q) {
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


    void add(const T& item) {
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
struct ProducerArg {
    Monitor<T>* monitor;
    int startValue;
};



template <typename T>
void* producer(void* argVoid) {
    auto arg = (ProducerArg<T>*)argVoid;
    auto monitor = arg->monitor;
    auto startValue = arg->startValue;

    int i = 1;

    for (;; ++i) {
        monitor->add(i + startValue);
    }

    pthread_exit(nullptr);
    return nullptr;
}



template <typename T>
void* consumer(void* argVoid) {
    auto monitor = (Monitor<T>*)argVoid;

    int data = 0;

    for (;;) {
        data = monitor->remove();
        cout << "Consumer " << data << endl;
        sleep(1);
    }

    pthread_exit(nullptr);
    return nullptr;
}



int main() {
    Monitor<int> monitor;
    queue<int> qProduct;

    constexpr int MAX_QUEUE_SIZE = 6;
    constexpr int NUM_PRODUCERS = 3;
    constexpr int NUM_CONSUMERS = 2;

    pthread_t lstTidProducer[NUM_PRODUCERS];
    pthread_t lstTidConsumer[NUM_CONSUMERS];
    ProducerArg<int> argPro[NUM_PRODUCERS];

    int ret = 0;


    // PREPARE ARGUMENTS
    monitor.init(MAX_QUEUE_SIZE, &qProduct);

    for (int i = 0; i < NUM_PRODUCERS; ++i)
        argPro[i] = { &monitor, i * 1000 };


    // CREATE THREADS
    for (int i = 0; i < NUM_PRODUCERS; ++i) {
        ret = pthread_create(&lstTidProducer[i], nullptr, producer<int>, &argPro[i]);
    }

    for (int i = 0; i < NUM_CONSUMERS; ++i) {
        ret = pthread_create(&lstTidConsumer[i], nullptr, consumer<int>, &monitor);
    }


    // JOIN THREADS
    for (int i = 0; i < NUM_PRODUCERS; ++i) {
        ret = pthread_join(lstTidProducer[i], nullptr);
    }

    for (int i = 0; i < NUM_CONSUMERS; ++i) {
        ret = pthread_join(lstTidConsumer[i], nullptr);
    }


    monitor.destroy();


    return 0;
}
