/*
BLOCKING QUEUE IMPLEMENTATION
Version B01: General blocking queues
             Underlying mechanism: Semaphores
*/


#include <iostream>
#include <queue>
#include <string>
#include <stdexcept>
#include <boost/chrono.hpp>
#include <boost/thread.hpp>
#include "mylib-semaphore.hpp"
using namespace std;



template <typename T>
class BlockingQueue {

private:
    int capacity;

    mylib::Semaphore semRemain;
    mylib::Semaphore semFill;
    boost::mutex mut;

    std::queue<T> q;


public:
    BlockingQueue(int capacity) : capacity(capacity), semRemain(capacity), semFill(0) {
        if (this->capacity <= 0)
            throw std::invalid_argument("capacity must be a positive integer");
    }


    void put(const T& value) {
        semRemain.acquire();

        {
            boost::unique_lock<boost::mutex> lk(mut);
            q.push(value);
        }

        semFill.release();
    }


    T take() {
        T result;
        semFill.acquire();

        {
            boost::unique_lock<boost::mutex> lk(mut);
            result = q.front();
            q.pop();
        }

        semRemain.release();
        return result;
    }

};



void producer(BlockingQueue<std::string>* blkQueue) {
    std::string arr[] = { "nice", "to", "meet", "you" };

    for (int i = 0; i < 4; ++i) {
        std::string& data = arr[i];
        cout << "Producer: " << data << endl;
        blkQueue->put(data);
        cout << "Producer: " << data << "\t\t\t[done]" << endl;
    }
}



void consumer(BlockingQueue<std::string>* blkQueue) {
    std::string data;
    boost::this_thread::sleep_for(boost::chrono::seconds(5));

    for (int i = 0; i < 4; ++i) {
        data = blkQueue->take();
        cout << "\tConsumer: " << data << endl;

        if (0 == i)
            boost::this_thread::sleep_for(boost::chrono::seconds(5));
    }
}



int main() {
    BlockingQueue<std::string> blkQueue(2); // capacity = 2

    boost::thread thProducer(&producer, &blkQueue);
    boost::thread thConsumer(&consumer, &blkQueue);

    thProducer.join();
    thConsumer.join();

    return 0;
}
