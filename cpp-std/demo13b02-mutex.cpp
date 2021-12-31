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
#include <thread>
#include <mutex>
#include <chrono>
using namespace std;



std::mutex mut;
int counter = 0;



void doTask() {
    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::unique_lock<std::mutex> lk(mut);

    for (int i = 0; i < 10000; ++i)
        ++counter;

    lk.unlock();

    // do something...
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
