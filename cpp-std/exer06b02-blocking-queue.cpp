/*
BLOCKING QUEUE IMPLEMENTATION
Version B02: General blocking queue
             Underlying mechanism: Condition variable
*/


#include <iostream>
#include <queue>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <stdexcept>
using namespace std;



template <typename T>
class BlockingQueue {

private:
    std::condition_variable condEmpty;
    std::condition_variable condFull;
    std::mutex mutEmpty;
    std::mutex mutFull;

    int capacity = 0;

    std::mutex mutLst;
    std::queue<T> q;


public:
    BlockingQueue(int capacity) {
        if (capacity <= 0)
            throw std::invalid_argument("capacity must be a positive integer");

        this->capacity = capacity;
    }


    void put(const T&& value) {
        {
            std::unique_lock<std::mutex> lk(mutFull);

            while (capacity == (int)q.size()) {
                // queue is full, must wait for 'take'
                condFull.wait(lk);
            }
        }

        {
            std::unique_lock<std::mutex> lk(mutLst);
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
            std::unique_lock<std::mutex> lk(mutLst);
            result = q.front();
            q.pop();
        }

        condFull.notify_one();
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
