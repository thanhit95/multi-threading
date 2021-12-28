/*
MUTEXES
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

    if (false == mut.try_lock()) {
        return;
    }

    for (int i = 0; i < 1000; ++i)
        ++counter;

    mut.unlock();
}



int main() {
    constexpr int NUM_THREADS = 3;
    std::thread lstTh[NUM_THREADS];


    counter = 0;


    for (auto&& th : lstTh) {
        th = std::thread(routineCounter);
    }


    for (auto&& th : lstTh) {
        th.join();
    }


    cout << "counter = " << counter << endl;
    return 0;
}
