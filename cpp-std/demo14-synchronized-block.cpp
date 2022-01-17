/*
SYNCHRONIZED BLOCKS

Synchronized blocks in C++ std threading are not supported by default.
To demonstate synchronized blocks, I use std::unique_lock (or std::lock_guard, std::scoped_lock).

Now, let's see the code:
    {
        std::unique_lock lk(mut);
        // Do something in the critical section
    }

The code block above is protected by a lock/mutex. That means it is synchronized on thread execution.
This code block is called "the synchronized block".
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

    // This is the "synchronized block"
    {
        std::unique_lock<std::mutex> lk(mut);

        for (int i = 0; i < 10000; ++i)
            ++counter;
    }
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
