/*
BLOCKING QUEUE IMPLEMENTATION
Version B01: General blocking queue / underlying mechanism: semaphore
*/


#include <iostream>
#include <list>
#include <string>
#include <stdexcept>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
using namespace std;



template <typename T>
class BlockingQueue {

private:
    sem_t semRemain;
    sem_t semFill;

    int capacity = 0;

    pthread_mutex_t mutLst = PTHREAD_MUTEX_INITIALIZER;
    std::list<T> lst;


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
        pthread_mutex_destroy(&mutLst);
    }


    void put(const T&& value) {
        int ret = 0;

        ret = sem_wait(&semRemain);

        ret = pthread_mutex_lock(&mutLst);
        lst.push_back(value);
        ret = pthread_mutex_unlock(&mutLst);

        ret = sem_post(&semFill);
    }


    T take() {
        T result;
        int ret = 0;

        ret = sem_wait(&semFill);

        ret = pthread_mutex_lock(&mutLst);
        result = lst.front();
        lst.pop_front();
        ret = pthread_mutex_unlock(&mutLst);

        ret = sem_post(&semRemain);

        return result;
    }

};



void* producer(void* arg) {
    auto queue = (BlockingQueue<std::string>*) arg;

    auto arr = { "nice", "to", "meet", "you" };

    for (auto&& value : arr) {
        cout << "Producer: " << value << endl;
        queue->put(value);
        cout << "Producer: " << value << "\t\t\t[done]" << endl;
    }

    pthread_exit(nullptr);
    return nullptr;
}



void* consumer(void* arg) {
    auto queue = (BlockingQueue<std::string>*) arg;

    sleep(5);

    for (int i = 0; i < 4; ++i) {
        std::string data = queue->take();
        cout << "\tConsumer: " << data << endl;

        if (0 == i)
            sleep(5);
    }

    pthread_exit(nullptr);
    return nullptr;
}



int main() {
    BlockingQueue<std::string> queue(2); // capacity = 2

    pthread_t tidProducer, tidConsumer;
    int ret = 0;

    ret = pthread_create(&tidProducer, nullptr, producer, &queue);
    ret = pthread_create(&tidConsumer, nullptr, consumer, &queue);

    ret = pthread_join(tidProducer, nullptr);
    ret = pthread_join(tidConsumer, nullptr);

    return 0;
}
