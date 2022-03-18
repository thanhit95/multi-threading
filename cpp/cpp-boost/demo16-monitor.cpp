/*
MONITORS
Implementation of a monitor for managing a counter
*/


#include <iostream>
#include <boost/chrono.hpp>
#include <boost/thread.hpp>
using namespace std;



class Monitor {
private:
    boost::mutex mut;
    int* pCounter;


public:
    // Should disable copy/move constructors, copy/move assignment operators


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
    boost::this_thread::sleep_for(boost::chrono::seconds(1));

    for (int i = 0; i < 1000; ++i)
        monitor->increaseCounter();
}



int main() {
    int counter = 0;
    Monitor monitor;

    const int NUM_THREADS = 16;
    boost::thread_group lstTh;

    monitor.init(&counter);

    for (int i = 0; i < NUM_THREADS; ++i) {
        lstTh.add_thread(new boost::thread(&doTask, &monitor));
    }

    lstTh.join_all();

    cout << "counter = " << counter << endl;
    return 0;
}
