/*
BLOCKING QUEUE IMPLEMENTATION
Version A: Synchronous queues
*/


#include <iostream>
#include <string>
#include <boost/chrono.hpp>
#include <boost/thread.hpp>
#include "mylib-semaphore.hpp"
using namespace std;



template <typename T>
class SynchronousQueue {

private:
    mylib::Semaphore semPut;
    mylib::Semaphore semTake;
    T element;


public:
    SynchronousQueue() : semPut(1), semTake(0) { }


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
    std::string arr[] = { "lorem", "ipsum", "dolor" };

    for (int i = 0; i < 3; ++i) {
        std::string& data = arr[i];
        cout << "Producer: " << data << endl;
        syncQueue->put(data);
        cout << "Producer: " << data << "\t\t\t[done]" << endl;
    }
}



void consumer(SynchronousQueue<std::string>* syncQueue) {
    std::string data;
    boost::this_thread::sleep_for(boost::chrono::seconds(5));

    for (int i = 0; i < 3; ++i) {
        data = syncQueue->take();
        cout << "\tConsumer: " << data << endl;
    }
}



int main() {
    SynchronousQueue<std::string> syncQueue;

    boost::thread thProducer(&producer, &syncQueue);
    boost::thread thConsumer(&consumer, &syncQueue);

    thProducer.join();
    thConsumer.join();

    return 0;
}
