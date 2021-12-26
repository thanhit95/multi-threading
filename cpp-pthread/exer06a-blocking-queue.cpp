/*
BLOCKING QUEUE IMPLEMENTATION
Version A: Synchronous queue
*/


#include <iostream>
#include <string>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
using namespace std;



template <typename T>
class SynchronousQueue {

private:
    sem_t semPut;
    sem_t semTake;
    T element;


public:
    SynchronousQueue<T>() {
        sem_init(&semPut, 0, 1);
        sem_init(&semTake, 0, 0);
    }


    ~SynchronousQueue<T>() {
        sem_destroy(&semPut);
        sem_destroy(&semTake);
    }


    void put(const T&& value) {
        sem_wait(&semPut);
        element = value;
        sem_post(&semTake);
    }


    T take() {
        sem_wait(&semTake);
        sem_post(&semPut);
        return element;
    }

};



void* producer(void* arg) {
    auto queue = (SynchronousQueue<std::string>*) arg;

    auto arr = { "lorem", "ipsum", "foo" };

    for (auto&& value : arr) {
        cout << "Producer: " << value << endl;
        queue->put(value);
        cout << "Producer: " << value << "\t\t\t[done]" << endl;
    }

    pthread_exit(nullptr);
    return nullptr;
}



void* consumer(void* arg) {
    auto queue = (SynchronousQueue<std::string>*) arg;

    sleep(5);

    for (int i = 0; i < 3; ++i) {
        std::string data = queue->take();
        cout << "\tConsumer: " << data << endl;
    }

    pthread_exit(nullptr);
    return nullptr;
}



int main() {
    SynchronousQueue<std::string> queue;

    pthread_t tidProducer, tidConsumer;
    int ret = 0;

    ret = pthread_create(&tidProducer, nullptr, producer, &queue);
    ret = pthread_create(&tidConsumer, nullptr, consumer, &queue);

    ret = pthread_join(tidProducer, nullptr);
    ret = pthread_join(tidConsumer, nullptr);

    return 0;
}
