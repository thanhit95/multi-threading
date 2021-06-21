#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std;



class Monitor {
private:
    std::mutex mut;
    int *pCounter = nullptr;


public:
    void init(int *pCounter) {
        this->pCounter = pCounter;
    }


    void increaseCounter() {
        mut.lock();

        (*pCounter) += 1;

        mut.unlock();
    }
};



void routineCounter(Monitor *monitor) {
    std::this_thread::sleep_for(std::chrono::seconds(1));

    for (int i = 0; i < 1000; ++i)
        monitor->increaseCounter();
}



int main() {
    int counter = 0;
    Monitor monitor;

    constexpr int NUM_THREADS = 3;
    std::thread lstTh[NUM_THREADS];


    monitor.init(&counter);


    for (auto&& th : lstTh) {
        th = std::thread(routineCounter, &monitor);
    }


    for (auto&& th : lstTh) {
        th.join();
    }


    cout << "counter = " << counter << endl;
    return 0;
}
