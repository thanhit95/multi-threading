/*
BLOCKING QUEUE IMPLEMENTATION
Version B01: General blocking queues
             Underlying mechanism: Semaphores
*/


#include <iostream>
#include <queue>
#include <string>
#include <chrono>
#include <stdexcept>
#include <thread>
#include <mutex>
#include <semaphore>
using namespace std;



using cntsemaphore = std::counting_semaphore<>;



template <typename T>
class BlockingQueue {

private:
    int capacity;

    cntsemaphore semRemain;
    cntsemaphore semFill;
    std::mutex mut;

    std::queue<T> q;


public:
    BlockingQueue(int capacity) : capacity(capacity), semRemain(capacity), semFill(0) {
        if (this->capacity <= 0)
            throw std::invalid_argument("capacity must be a positive integer");
    }


    void put(const T& value) {
        semRemain.acquire();

        {
            std::unique_lock<std::mutex> lk(mut);
            q.push(value);
        }

        semFill.release();
    }


    T take() {
        T result;
        semFill.acquire();

        {
            std::unique_lock<std::mutex> lk(mut);
            result = q.front();
            q.pop();
        }

        semRemain.release();
        return result;
    }

};



void producer(BlockingQueue<std::string>* blkQueue) {
    auto arr = { "nice", "to", "meet", "you" };

    for (auto&& data : arr) {
        cout << "Producer: " << data << endl;
        blkQueue->put(data);
        cout << "Producer: " << data << "\t\t\t[done]" << endl;
    }
}



void consumer(BlockingQueue<std::string>* blkQueue) {
    std::string data;
    std::this_thread::sleep_for(std::chrono::seconds(5));

    for (int i = 0; i < 4; ++i) {
        data = blkQueue->take();
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
