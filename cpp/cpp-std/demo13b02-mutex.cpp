/*
MUTEXES

- std::lock_guard will be locked only once on construction and unlocked on destruction.
- In contrast to std::lock_guard, std::unique_lock can be:
  + created without immediately locking, and
  + unlocked at any point in its existence.

Furthermore, C++17 introduces a new lock class called std::scoped_lock.
The std::scoped_lock is a strictly superior version of std::lock_guard that
locks an arbitrary number of mutexes all at once.
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

    std::unique_lock<std::mutex> lk(mut);
    // std::scoped_lock<std::mutex> lk(mut);

    for (int i = 0; i < 1000; ++i)
        ++counter;

    lk.unlock();

    // Do something...
}



int main() {
    constexpr int NUM_THREADS = 16;
    std::thread lstTh[NUM_THREADS];

    for (auto&& th : lstTh) {
        th = std::thread(&doTask);
    }

    for (auto&& th : lstTh) {
        th.join();
    }

    cout << "counter = " << counter << endl;
    // We are sure that counter = 16000

    return 0;
}
