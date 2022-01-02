/*
MONITORS
Implementation of a monitor for managing a counter
*/


#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
using namespace std;



class Monitor {
private:
    std::mutex mut;
    int* pCounter = nullptr;


public:
    // should disable copy/move constructors, copy/move assignment operators


    void init(int* pCounter) {
        this->pCounter = pCounter;
    }


    void increaseCounter() {
        mut.lock();
        (*pCounter) += 1;
        mut.unlock();
    }
};



void doTask(Monitor* monitor) {
    std::this_thread::sleep_for(std::chrono::seconds(1));

    for (int i = 0; i < 10000; ++i)
        monitor->increaseCounter();
}



int main() {
    int counter = 0;
    Monitor monitor;

    constexpr int NUM_THREADS = 3;
    std::thread lstTh[NUM_THREADS];


    monitor.init(&counter);


    for (auto&& th : lstTh) {
        th = std::thread(doTask, &monitor);
    }


    for (auto&& th : lstTh) {
        th.join();
    }


    cout << "counter = " << counter << endl;
    return 0;
}
