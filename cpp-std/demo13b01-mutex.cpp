/*
MUTEXES

Without synchronization (by a mutex), we are not sure that result = 30000.

std::lock_guard is a class template, which implements the RAII for mutex.
It wraps the mutex inside it’s object and locks the attached mutex in its constructor.
When it’s destructor is called it releases the mutex.
*/


#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
using namespace std;



std::mutex mut;
int counter = 0;



void doTask() {
    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::lock_guard<std::mutex> lk(mut);

    for (int i = 0; i < 10000; ++i)
        ++counter;

    // Once function exits, then destructor of lk object will be called.
    // In destructor it unlocks the mutex.
}



int main() {
    constexpr int NUM_THREADS = 3;
    std::thread lstTh[NUM_THREADS];


    for (auto&& th : lstTh) {
        th = std::thread(doTask);
    }


    for (auto&& th : lstTh) {
        th.join();
    }


    cout << "counter = " << counter << endl;
    return 0;
}
