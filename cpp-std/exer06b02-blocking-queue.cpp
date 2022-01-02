/*
BLOCKING QUEUE IMPLEMENTATION
Version B02: General blocking queues
             Underlying mechanism: Condition variables
*/


#include <iostream>
#include <queue>
#include <string>
#include <chrono>
#include <stdexcept>
#include <thread>
#include <mutex>
#include <condition_variable>
using namespace std;



template <typename T>
class BlockingQueue {

private:
    /*
    I use a lot of synchronization primitives to help you to understand.
    In a practical context, please take a look at
    the BlockingQueue implementation in "mylib-blockingqueue"
    */
    std::condition_variable condEmpty;
    std::condition_variable condFull;
    std::mutex mutEmpty;
    std::mutex mutFull;
    std::mutex mutQueue;

    int capacity = 0;
    std::queue<T> q;


public:
    BlockingQueue(int capacity) {
        if (capacity <= 0)
            throw std::invalid_argument("capacity must be a positive integer");

        this->capacity = capacity;
    }


    void put(const T& value) {
        {
            std::unique_lock<std::mutex> lk(mutFull);

            while (capacity == (int)q.size()) {
                // queue is full, must wait for 'take'
                condFull.wait(lk);
            }
        }

        {
            std::unique_lock<std::mutex> lk(mutQueue);
            q.push(value);
        }

        condEmpty.notify_one();
    }


    T take() {
        T result;

        {
            std::unique_lock<std::mutex> lk(mutEmpty);

            while (0 == q.size()) {
                // queue is empty, must wait for 'put'
                condEmpty.wait(lk);
            }
        }

        {
            std::unique_lock<std::mutex> lk(mutQueue);
            result = q.front();
            q.pop();
        }

        condFull.notify_one();
        return result;
    }

};



void producer(BlockingQueue<std::string>* blkQueue) {
    auto arr = { "nice", "to", "meet", "you" };

    for (auto&& value : arr) {
        cout << "Producer: " << value << endl;
        blkQueue->put(value);
        cout << "Producer: " << value << "\t\t\t[done]" << endl;
    }
}



void consumer(BlockingQueue<std::string>* blkQueue) {
    std::this_thread::sleep_for(std::chrono::seconds(5));

    for (int i = 0; i < 4; ++i) {
        std::string data = blkQueue->take();
        cout << "\tConsumer: " << data << endl;

        if (0 == i)
            std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}



int main() {
    BlockingQueue<std::string> blkQueue(2); // capacity = 2

    auto thProducer = std::thread(producer, &blkQueue);
    auto thConsumer = std::thread(consumer, &blkQueue);

    thProducer.join();
    thConsumer.join();

    return 0;
}
