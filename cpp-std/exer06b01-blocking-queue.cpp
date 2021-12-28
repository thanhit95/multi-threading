/*
BLOCKING QUEUE IMPLEMENTATION
Version B01: General blocking queues
             Underlying mechanism: Semaphores
*/


#include <iostream>
#include <queue>
#include <string>
#include <thread>
#include <mutex>
#include <semaphore>
#include <chrono>
#include <stdexcept>
using namespace std;



using TypeSemaphore = std::counting_semaphore<>;



template <typename T>
class BlockingQueue {

private:
    int capacity;

    TypeSemaphore semRemain;
    TypeSemaphore semFill;

    std::mutex mutLst;
    std::queue<T> q;


public:
    BlockingQueue(int capacity) : capacity(capacity), semRemain(capacity), semFill(0) {
        if (this->capacity <= 0)
            throw std::invalid_argument("capacity must be a positive integer");
    }


    void put(const T&& value) {
        semRemain.acquire();

        {
            std::unique_lock<std::mutex> lk(mutLst);
            q.push(value);
        }

        semFill.release();
    }


    T take() {
        T result;
        semFill.acquire();

        {
            std::unique_lock<std::mutex> lk(mutLst);
            result = q.front();
            q.pop();
        }

        semRemain.release();
        return result;
    }

};



void producer(BlockingQueue<std::string>* queue) {
    auto arr = { "nice", "to", "meet", "you" };

    for (auto&& value : arr) {
        cout << "Producer: " << value << endl;
        queue->put(value);
        cout << "Producer: " << value << "\t\t\t[done]" << endl;
    }
}



void consumer(BlockingQueue<std::string>* queue) {
    std::this_thread::sleep_for(std::chrono::seconds(5));

    for (int i = 0; i < 4; ++i) {
        std::string data = queue->take();
        cout << "\tConsumer: " << data << endl;

        if (0 == i)
            std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}



int main() {
    BlockingQueue<std::string> queue(2); // capacity = 2

    auto thProducer = std::thread(producer, &queue);
    auto thConsumer = std::thread(consumer, &queue);

    thProducer.join();
    thConsumer.join();

    return 0;
}
