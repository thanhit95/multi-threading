/*
MUTEXES
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

    mut.lock();

    for (int i = 0; i < 1000; ++i)
        ++counter;

    mut.unlock();
}



int main() {
    constexpr int NUM_THREADS = 16;
    std::thread lstTh[NUM_THREADS];

    for (auto&& th : lstTh) {
        th = std::thread(doTask);
    }

    for (auto&& th : lstTh) {
        th.join();
    }

    cout << "counter = " << counter << endl;
    // We are sure that counter = 16000

    return 0;
}
