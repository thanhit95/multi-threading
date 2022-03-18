/*
BLOCKING QUEUE IMPLEMENTATION
Version B02: General blocking queues
             Underlying mechanism: Condition variables
*/


#include <iostream>
#include <queue>
#include <string>
#include <stdexcept>
#include <boost/chrono.hpp>
#include <boost/thread.hpp>
using namespace std;



template <typename T>
class BlockingQueue {

private:
    boost::condition_variable condEmpty;
    boost::condition_variable condFull;
    boost::mutex mut;

    int capacity;
    std::queue<T> q;


public:
    BlockingQueue(int capacity) {
        if (capacity <= 0)
            throw std::invalid_argument("capacity must be a positive integer");

        this->capacity = capacity;
    }


    void put(const T& value) {
        {
            boost::unique_lock<boost::mutex> lk(mut);

            while (capacity == (int)q.size()) {
                // Queue is full, must wait for 'take'
                condFull.wait(lk);
            }

            q.push(value);
        }

        condEmpty.notify_one();
    }


    T take() {
        T result;

        {
            boost::unique_lock<boost::mutex> lk(mut);

            while (0 == q.size()) {
                // Queue is empty, must wait for 'put'
                condEmpty.wait(lk);
            }

            result = q.front();
            q.pop();
        }

        condFull.notify_one();
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
