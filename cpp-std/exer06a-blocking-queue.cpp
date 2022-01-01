/*
BLOCKING QUEUE IMPLEMENTATION
Version A: Synchronous queues
*/


#include <iostream>
#include <string>
#include <thread>
#include <semaphore>
#include <chrono>
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
        semPut.release();
        return element;
    }

};



void producer(SynchronousQueue<std::string>* syncQueue) {
    auto arr = { "lorem", "ipsum", "dolor" };

    for (auto&& value : arr) {
        cout << "Producer: " << value << endl;
        syncQueue->put(value);
        cout << "Producer: " << value << "\t\t\t[done]" << endl;
    }
}



void consumer(SynchronousQueue<std::string>* syncQueue) {
    std::this_thread::sleep_for(std::chrono::seconds(5));

    for (int i = 0; i < 3; ++i) {
        std::string data = syncQueue->take();
        cout << "\tConsumer: " << data << endl;
    }
}



int main() {
    SynchronousQueue<std::string> syncQueue;

    auto thProducer = std::thread(producer, &syncQueue);
    auto thConsumer = std::thread(consumer, &syncQueue);

    thProducer.join();
    thConsumer.join();

    return 0;
}
