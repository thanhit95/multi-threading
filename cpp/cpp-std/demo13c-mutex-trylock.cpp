/*
MUTEXES
Locking with a nonblocking mutex
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

    if (false == mut.try_lock()) {
        return;
    }

    for (int i = 0; i < 10000; ++i)
        ++counter;

    mut.unlock();
}



int main() {
    constexpr int NUM_THREADS = 3;
    std::thread lstTh[NUM_THREADS];

    for (auto&& th : lstTh) {
        th = std::thread(&doTask);
    }

    for (auto&& th : lstTh) {
        th.join();
    }

    cout << "counter = " << counter << endl;
    // counter can be 10000, 20000 or 30000

    return 0;
}
