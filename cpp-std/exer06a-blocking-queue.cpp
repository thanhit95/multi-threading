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



using TypeSemaphore = std::counting_semaphore<>;



template <typename T>
class SynchronousQueue {

private:
    TypeSemaphore semPut = TypeSemaphore(1);
    TypeSemaphore semTake = TypeSemaphore(0);
    T element;


public:
    void put(const T&& value) {
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



void producer(SynchronousQueue<std::string>* queue) {
    auto arr = { "lorem", "ipsum", "foo" };

    for (auto&& value : arr) {
        cout << "Producer: " << value << endl;
        queue->put(value);
        cout << "Producer: " << value << "\t\t\t[done]" << endl;
    }
}



void consumer(SynchronousQueue<std::string>* queue) {
    std::this_thread::sleep_for(std::chrono::seconds(5));

    for (int i = 0; i < 3; ++i) {
        std::string data = queue->take();
        cout << "\tConsumer: " << data << endl;
    }
}



int main() {
    SynchronousQueue<std::string> queue;

    auto thProducer = std::thread(producer, &queue);
    auto thConsumer = std::thread(consumer, &queue);

    thProducer.join();
    thConsumer.join();

    return 0;
}
