/*
READ-WRITE LOCKS
*/


#include <iostream>
#include <thread>
#include <shared_mutex>
#include <chrono>
#include "mytool-random.hpp"
using namespace std;



volatile int resource = 0;
auto rwlock = std::shared_mutex();



void routineRead(int timeWait) {
    std::this_thread::sleep_for(std::chrono::seconds(timeWait));

    rwlock.lock_shared();

    cout << "routineRead: " << resource << endl;

    rwlock.unlock_shared();
}



void routineWrite(int timeWait) {
    std::this_thread::sleep_for(std::chrono::seconds(timeWait));

    rwlock.lock();

    resource = mytool::RandInt::staticGet() % 100;
    cout << "routineWrite: " << resource << endl;

    rwlock.unlock();
}



int main() {
    constexpr int NUM_THREADS_READ = 10;
    constexpr int NUM_THREADS_WRITE = 4;
    constexpr int NUM_ARGS = 3;

    std::thread lstThRead[NUM_THREADS_READ];
    std::thread lstThWrite[NUM_THREADS_WRITE];
    int arg[NUM_ARGS];

    mytool::RandInt randInt(1, 1000);


    // INITIALIZE
    for (int i = 0; i < NUM_ARGS; ++i) {
        arg[i] = i;
    }


    // CREATE THREADS
    for (auto&& th : lstThRead) {
        int argIndex = randInt.get() % NUM_ARGS;
        th = std::thread(routineRead, arg[argIndex]);
    }

    for (auto&& th : lstThWrite) {
        int argIndex = randInt.get() % NUM_ARGS;
        th = std::thread(routineWrite, arg[argIndex]);
    }


    // JOIN THREADS
    for (auto&& th : lstThRead) {
        th.join();
    }

    for (auto&& th : lstThWrite) {
        th.join();
    }


    return 0;
}
