/*
THE PRODUCER-CONSUMER PROBLEM

SOLUTION TYPE C: USING CONDITION VARIABLES & MONITORS
    Multiple fast producers, multiple slow consumers
*/


#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
using namespace std;



template <typename T>
class Monitor {
private:
    std::queue<T>* q = nullptr;
    int maxQueueSize = 0;

    std::condition_variable condFull;
    std::condition_variable condEmpty;
    std::mutex mut;


public:
    Monitor() = default;
    Monitor(const Monitor& other) = delete;
    Monitor(const Monitor&& other) = delete;
    void operator=(const Monitor& other) = delete;
    void operator=(const Monitor&& other) = delete;


    void init(int maxQueueSize, std::queue<T>* q) {
        this->q = q;
        this->maxQueueSize = maxQueueSize;
    }


    void add(const T& item) {
        std::unique_lock<std::mutex> mutLock(mut);

        while (q->size() == maxQueueSize) {
            condFull.wait(mutLock);
        }

        q->push(item);

        if (q->size() == 1) {
            condEmpty.notify_one();
        }

        // mutLock.unlock();
    }


    T remove() {
        std::unique_lock<std::mutex> mutLock(mut);

        while (q->size() == 0) {
            condEmpty.wait(mutLock);
        }

        T item = q->front();
        q->pop();

        if (q->size() == maxQueueSize - 1) {
            condFull.notify_one();
        }

        // mutLock.unlock();

        return item;
    }
};



template <typename T>
void producer(Monitor<T>* monitor, int startValue) {
    T i = 1;

    for (;; ++i) {
        monitor->add(i + startValue);
    }
}



template <typename T>
void consumer(Monitor<T>* monitor) {
    T data = 0;

    for (;;) {
        data = monitor->remove();
        cout << "Consumer " << data << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}



int main() {
    Monitor<int> monitor;
    queue<int> qProduct;

    constexpr int MAX_QUEUE_SIZE = 6;
    constexpr int NUM_PRODUCERS = 3;
    constexpr int NUM_CONSUMERS = 2;

    std::thread lstThProducer[NUM_PRODUCERS];
    std::thread lstThConsumer[NUM_CONSUMERS];


    // PREPARE ARGUMENTS
    monitor.init(MAX_QUEUE_SIZE, &qProduct);


    // CREATE THREADS
    for (int i = 0; i < NUM_PRODUCERS; ++i) {
        lstThProducer[i] = std::thread(producer<int>, &monitor, i * 1000);
    }

    for (auto&& th : lstThConsumer) {
        th = std::thread(consumer<int>, &monitor);
    }


    // JOIN THREADS
    for (auto&& th : lstThProducer) {
        th.join();
    }

    for (auto&& th : lstThConsumer) {
        th.join();
    }


    return 0;
}
