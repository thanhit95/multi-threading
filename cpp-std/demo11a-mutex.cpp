#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std;



std::mutex mut;
int count = 0;



void routineCounter() {
    std::this_thread::sleep_for(std::chrono::seconds(1));

    mut.lock();

    for (int i = 0; i < 1000; ++i)
        ++count;

    mut.unlock();
}



int main() {
    constexpr int NUM_THREADS = 3;
    std::thread lstTh[NUM_THREADS];


    count = 0;


    for (auto &&th : lstTh) {
        th = std::thread(routineCounter);
    }


    for (auto &&th : lstTh) {
        th.join();
    }


    cout << "count = " << count << endl;
    return 0;
}
