/*
BLOCKING QUEUE IMPLEMENTATION
Version B: General blocking queue
*/


#include <iostream>
#include <list>
#include <string>
#include <stdexcept>
#include <pthread.h>
#include <unistd.h>
using namespace std;



template <typename T>
class BlockingQueue {

private:
    pthread_cond_t condEmpty = PTHREAD_COND_INITIALIZER;
    pthread_cond_t condFull = PTHREAD_COND_INITIALIZER;
    pthread_mutex_t mutEmpty = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_t mutFull = PTHREAD_MUTEX_INITIALIZER;

    int capacity = 0;

    pthread_mutex_t mutLst = PTHREAD_MUTEX_INITIALIZER;
    std::list<T> lst;


public:
    BlockingQueue<T>(int capacity) {
        if (capacity <= 0)
            throw std::invalid_argument("capacity must be a positive integer");

        this->capacity = capacity;
    }


    ~BlockingQueue<T>() {
        pthread_cond_destroy(&condEmpty);
        pthread_cond_destroy(&condFull);
        pthread_mutex_destroy(&mutEmpty);
        pthread_mutex_destroy(&mutFull);
        pthread_mutex_destroy(&mutLst);
    }


    void put(const T&& value) {
        int ret = 0;


        ret = pthread_mutex_lock(&mutFull);

        while (capacity == lst.size()) {
            // queue is full, must wait for 'take'
            ret = pthread_cond_wait(&condFull, &mutFull);
        }

        ret = pthread_mutex_unlock(&mutFull);


        ret = pthread_mutex_lock(&mutLst);
        lst.push_back(value);
        ret = pthread_mutex_unlock(&mutLst);


        ret = pthread_cond_signal(&condEmpty);
    }


    T take() {
        T result;
        int ret = 0;


        ret = pthread_mutex_lock(&mutEmpty);

        while (0 == lst.size()) {
            // queue is empty, must wait for 'put'
            ret = pthread_cond_wait(&condEmpty, &mutEmpty);
        }

        ret = pthread_mutex_unlock(&mutEmpty);


        ret = pthread_mutex_lock(&mutLst);
        result = lst.front();
        lst.pop_front();
        ret = pthread_mutex_unlock(&mutLst);


        ret = pthread_cond_signal(&condFull);


        return result;
    }

};



void* producer(void* arg) {
    auto queue = (BlockingQueue<std::string>*) arg;

    auto arr = { "nice", "to", "meet", "you" };

    for (auto&& value : arr) {
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
