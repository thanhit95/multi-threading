/*
THE PRODUCER-CONSUMER PROBLEM

SOLUTION TYPE C: USING CONDITION VARIABLES & MONITORS
    Multiple fast producers, multiple slow consumers
*/


#include <iostream>
#include <queue>
#include <boost/chrono.hpp>
#include <boost/thread.hpp>
using namespace std;



template <typename T>
class Monitor {
private:
    std::queue<T>* q;
    int maxQueueSize;

    boost::condition_variable condFull;
    boost::condition_variable condEmpty;
    boost::mutex mut;


public:
    Monitor() : q(0), maxQueueSize(0) { }


private:
    Monitor(const Monitor& other) { }
    void operator=(const Monitor& other) { }


public:
    void init(int maxQueueSize, std::queue<T>* q) {
        this->q = q;
        this->maxQueueSize = maxQueueSize;
    }


    void add(const T& item) {
        boost::unique_lock<boost::mutex> mutLock(mut);

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
        boost::unique_lock<boost::mutex> mutLock(mut);

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
    T data;

    for (;;) {
        data = monitor->remove();
        cout << "Consumer " << data << endl;
        boost::this_thread::sleep_for(boost::chrono::seconds(1));
    }
}



int main() {
    Monitor<int> monitor;
    queue<int> q;

    const int MAX_QUEUE_SIZE = 6;
    const int NUM_PRODUCERS = 3;
    const int NUM_CONSUMERS = 2;

    boost::thread_group lstThProducer;
    boost::thread_group lstThConsumer;


    // PREPARE ARGUMENTS
    monitor.init(MAX_QUEUE_SIZE, &q);


    // CREATE THREADS
    for (int i = 0; i < NUM_PRODUCERS; ++i) {
        lstThProducer.add_thread(new boost::thread(&producer<int>, &monitor, i * 1000));
    }

    for (int i = 0; i < NUM_CONSUMERS; ++i) {
        lstThConsumer.add_thread(new boost::thread(&consumer<int>, &monitor));
    }


    // JOIN THREADS
    lstThProducer.join_all();
    lstThConsumer.join_all();


    return 0;
}
