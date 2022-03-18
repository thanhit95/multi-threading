/*
BLOCKING QUEUE IMPLEMENTATION
Version A: Synchronous queues
*/


#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <semaphore>
using namespace std;



using cntsemaphore = std::counting_semaphore<>;



template <typename T>
class SynchronousQueue {

private:
    cntsemaphore semPut = cntsemaphore(1);
    cntsemaphore semTake = cntsemaphore(0);
    T element;


public:
    void put(const T& value) {
        semPut.acquire();
        element = value;
        semTake.release();
    }


    T take() {
        semTake.acquire();
        T result = element;
        semPut.release();
        return result;
    }

};



void producer(SynchronousQueue<std::string>* syncQueue) {
    auto arr = { "lorem", "ipsum", "dolor" };

    for (auto&& data : arr) {
        cout << "Producer: " << data << endl;
        syncQueue->put(data);
        cout << "Producer: " << data << "\t\t\t[done]" << endl;
    }
}



void consumer(SynchronousQueue<std::string>* syncQueue) {
    std::string data;
    std::this_thread::sleep_for(std::chrono::seconds(5));

    for (int i = 0; i < 3; ++i) {
        data = syncQueue->take();
        cout << "\tConsumer: " << data << endl;
    }
}



int main() {
    SynchronousQueue<std::string> syncQueue;

    auto thProducer = std::thread(&producer, &syncQueue);
    auto thConsumer = std::thread(&consumer, &syncQueue);

    thProducer.join();
    thConsumer.join();

    return 0;
}
