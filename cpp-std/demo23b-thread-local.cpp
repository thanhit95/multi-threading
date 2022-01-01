/*
THREAD-LOCAL STORAGE
Avoiding synchronization using thread-local storage
*/


#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
using namespace std;



thread_local int counter = 0;



void doTask(int t) {
    std::this_thread::sleep_for(std::chrono::seconds(1));

    for (int i = 0; i < 1000; ++i)
        ++counter;

    cout << "Thread " << t << " gives counter = " << counter << endl;
}



int main() {
    constexpr int NUM_THREADS = 3;
    vector<std::thread> lstTh;

    for (int i = 0; i < NUM_THREADS; ++i) {
        lstTh.push_back(std::thread(doTask, i));
    }

    for (auto&& th : lstTh) {
        th.join();
    }

    cout << endl;

    /*
    By using thread-local storage, each thread has its own counter.
    So, the counter in one thread is completely independent of each other.

    Thread-local storage helps us to AVOID SYNCHRONIZATION.
    */
    return 0;
}
