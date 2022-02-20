/*
REENTRANT LOCKS (RECURSIVE MUTEXES)
Version C: A slightly hard example
*/


#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
using namespace std;



std::recursive_mutex mut;



void doTask(char name) {
    std::this_thread::sleep_for(std::chrono::seconds(1));

    mut.lock();
    cout << "First time " << name << " acquiring the resource" << endl;

    mut.lock();
    cout << "Second time " << name << " acquiring the resource" << endl;

    mut.unlock();
    mut.unlock();
}



int main() {
    constexpr int NUM_THREADS = 3;
    std::thread lstTh[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; ++i) {
        lstTh[i] = std::thread(doTask, char(i + 'A'));
    }

    for (auto&& th : lstTh) {
        th.join();
    }

    return 0;
}
