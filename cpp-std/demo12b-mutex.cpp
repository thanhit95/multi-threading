/*
std::lock_guard is a class template, which implements the RAII for mutex.
It wraps the mutex inside it’s object and locks the attached mutex in its constructor.
When it’s destructor is called it releases the mutex.
*/


#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std;



std::mutex mut;
int counter = 0;



void routineCounter() {
    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::lock_guard<std::mutex> lockGuard(mut);

    for (int i = 0; i < 1000; ++i)
        ++counter;

    // Once function exits, then destructor of lockGuard object will be called.
    // In destructor it unlocks the mutex.
}



int main() {
    constexpr int NUM_THREADS = 3;
    std::thread lstTh[NUM_THREADS];


    counter = 0;


    for (auto &&th : lstTh) {
        th = std::thread(routineCounter);
    }


    for (auto &&th : lstTh) {
        th.join();
    }


    cout << "counter = " << counter << endl;
    return 0;
}
