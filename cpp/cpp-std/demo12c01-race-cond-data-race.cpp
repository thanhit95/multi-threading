/*
RACE CONDITIONS AND DATA RACES
*/


#include <iostream>
#include <chrono>
#include <thread>
using namespace std;



int counter = 0;



void increaseCounter() {
    std::this_thread::sleep_for(std::chrono::seconds(1));

    for (int i = 0; i < 1000; ++i) {
        counter += 1;
    }
}



int main() {
    constexpr int NUM_THREADS = 16;
    std::thread lstTh[NUM_THREADS];

    for (auto&& th : lstTh) {
        th = std::thread(&increaseCounter);
    }

    for (auto&& th : lstTh) {
        th.join();
    }

    cout << "counter = " << counter << endl;
    // We are NOT sure that counter = 16000

    return 0;
}
