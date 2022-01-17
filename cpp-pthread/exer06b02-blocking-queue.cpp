/*
BLOCKING QUEUE IMPLEMENTATION
Version B02: General blocking queues
             Underlying mechanism: Condition variables
*/


#include <iostream>
#include <queue>
#include <string>
#include <stdexcept>
#include <unistd.h>
#include <pthread.h>
using namespace std;



template <typename T>
class BlockingQueue {

private:
    /*
    I use a lot of synchronization primitives to help you to understand.
    In a practical context, please take a look at
    the BlockingQueue implementation in "mylib-blockingqueue"
    */
    pthread_cond_t condEmpty = PTHREAD_COND_INITIALIZER;
    pthread_cond_t condFull = PTHREAD_COND_INITIALIZER;
    pthread_mutex_t mutEmpty = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_t mutFull = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_t mutQueue = PTHREAD_MUTEX_INITIALIZER;

    int capacity = 0;
    std::queue<T> q;


public:
    BlockingQueue(int capacity) {
        if (capacity <= 0)
            throw std::invalid_argument("capacity must be a positive integer");

        this->capacity = capacity;
    }


    ~BlockingQueue() {
        pthread_cond_destroy(&condEmpty);
        pthread_cond_destroy(&condFull);
        pthread_mutex_destroy(&mutEmpty);
        pthread_mutex_destroy(&mutFull);
        pthread_mutex_destroy(&mutQueue);
    }


    void put(const T& value) {
        int ret = 0;


        ret = pthread_mutex_lock(&mutFull);

        while (capacity == q.size()) {
            // Queue is full, must wait for 'take'
            ret = pthread_cond_wait(&condFull, &mutFull);
        }

        ret = pthread_mutex_unlock(&mutFull);


        ret = pthread_mutex_lock(&mutQueue);
        q.push(value);
        ret = pthread_mutex_unlock(&mutQueue);


        ret = pthread_cond_signal(&condEmpty);
    }


    T take() {
        T result;
        int ret = 0;


        ret = pthread_mutex_lock(&mutEmpty);

        while (0 == q.size()) {
            // Queue is empty, must wait for 'put'
            ret = pthread_cond_wait(&condEmpty, &mutEmpty);
        }

        ret = pthread_mutex_unlock(&mutEmpty);


        ret = pthread_mutex_lock(&mutQueue);
        result = q.front();
        q.pop();
        ret = pthread_mutex_unlock(&mutQueue);


        ret = pthread_cond_signal(&condFull);
        return result;
    }

};



void* producer(void* arg) {
    auto blkQueue = (BlockingQueue<std::string>*) arg;

    auto arr = { "nice", "to", "meet", "you" };

    for (auto&& value : arr) {
        cout << "Producer: " << value << endl;
        blkQueue->put(value);
        cout << "Producer: " << value << "\t\t\t[done]" << endl;
    }

    pthread_exit(nullptr);
    return nullptr;
}



void* consumer(void* arg) {
    auto blkQueue = (BlockingQueue<std::string>*) arg;

    sleep(5);

    for (int i = 0; i < 4; ++i) {
        std::string data = blkQueue->take();
        cout << "\tConsumer: " << data << endl;

        if (0 == i)
            sleep(5);
    }

    pthread_exit(nullptr);
    return nullptr;
}



int main() {
    BlockingQueue<std::string> blkQueue(2); // capacity = 2

    pthread_t tidProducer, tidConsumer;
    int ret = 0;

    ret = pthread_create(&tidProducer, nullptr, producer, &blkQueue);
    ret = pthread_create(&tidConsumer, nullptr, consumer, &blkQueue);

    ret = pthread_join(tidProducer, nullptr);
    ret = pthread_join(tidConsumer, nullptr);

    return 0;
}
