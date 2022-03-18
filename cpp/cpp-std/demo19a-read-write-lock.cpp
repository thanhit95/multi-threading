/*
READ-WRITE LOCKS
*/


#include <iostream>
#include <numeric>
#include <chrono>
#include <thread>
#include <shared_mutex>
#include "mylib-random.hpp"
using namespace std;



volatile int resource = 0;
auto rwmut = std::shared_mutex();



void readFunc(int timeWait) {
    std::this_thread::sleep_for(std::chrono::seconds(timeWait));

    rwmut.lock_shared();

    cout << "read: " << resource << endl;

    rwmut.unlock_shared();
}



void writeFunc(int timeWait) {
    std::this_thread::sleep_for(std::chrono::seconds(timeWait));

    rwmut.lock();

    resource = mylib::RandInt::get(100);
    cout << "write: " << resource << endl;

    rwmut.unlock();
}



int main() {
    constexpr int NUM_THREADS_READ = 10;
    constexpr int NUM_THREADS_WRITE = 4;
    constexpr int NUM_ARGS = 3;

    std::thread lstThRead[NUM_THREADS_READ];
    std::thread lstThWrite[NUM_THREADS_WRITE];
    int lstArg[NUM_ARGS];


    // INITIALIZE
    // lstArg = { 0, 1, 2, ..., NUM_ARG - 1 }
    std::iota(lstArg, lstArg + NUM_ARGS, 0);


    // CREATE THREADS
    for (auto&& th : lstThRead) {
        int arg = lstArg[ mylib::RandInt::get(NUM_ARGS) ];
        th = std::thread(&readFunc, arg);
    }

    for (auto&& th : lstThWrite) {
        int arg = lstArg[ mylib::RandInt::get(NUM_ARGS) ];
        th = std::thread(&writeFunc, arg);
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
