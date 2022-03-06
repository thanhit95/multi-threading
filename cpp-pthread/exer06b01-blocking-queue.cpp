/*
BLOCKING QUEUE IMPLEMENTATION
Version B01: General blocking queues
             Underlying mechanism: Semaphores
*/


#include <iostream>
#include <queue>
#include <string>
#include <stdexcept>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
using namespace std;



template <typename T>
class BlockingQueue {

private:
    int capacity = 0;

    sem_t semRemain;
    sem_t semFill;
    pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

    std::queue<T> q;


public:
    BlockingQueue(int capacity) {
        if (capacity <= 0)
            throw std::invalid_argument("capacity must be a positive integer");

        this->capacity = capacity;

        sem_init(&semRemain, 0, capacity);
        sem_init(&semFill, 0, 0);
    }


    ~BlockingQueue() {
        sem_destroy(&semRemain);
        sem_destroy(&semFill);
        pthread_mutex_destroy(&mut);
    }


    void put(const T& value) {
        int ret = 0;

        ret = sem_wait(&semRemain);

        ret = pthread_mutex_lock(&mut);
        q.push(value);
        ret = pthread_mutex_unlock(&mut);

        ret = sem_post(&semFill);
    }


    T take() {
        T result;
        int ret = 0;

        ret = sem_wait(&semFill);

        ret = pthread_mutex_lock(&mut);
        result = q.front();
        q.pop();
        ret = pthread_mutex_unlock(&mut);

        ret = sem_post(&semRemain);

        return result;
    }

};



void* producer(void* arg) {
    auto blkQueue = (BlockingQueue<std::string>*) arg;

    auto arr = { "nice", "to", "meet", "you" };

    for (auto&& data : arr) {
        cout << "Producer: " << data << endl;
        blkQueue->put(data);
        cout << "Producer: " << data << "\t\t\t[done]" << endl;
    }

    pthread_exit(nullptr);
    return nullptr;
}



void* consumer(void* arg) {
    auto blkQueue = (BlockingQueue<std::string>*) arg;
    std::string data;

    sleep(5);

    for (int i = 0; i < 4; ++i) {
        data = blkQueue->take();
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
