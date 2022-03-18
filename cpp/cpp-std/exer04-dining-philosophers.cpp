/*
THE DINING PHILOSOPHERS PROBLEM
*/


#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
using namespace std;



void doTaskPhilosopher(std::mutex chopstick[], int numPhilo, int idPhilo) {
    int n = numPhilo;
    int i = idPhilo;

    std::this_thread::sleep_for(std::chrono::seconds(1));

    chopstick[i].lock();
    chopstick[(i + 1) % n].lock();

    cout << "Philosopher #" << i << " is eating the rice" << endl;

    chopstick[i].unlock();
    chopstick[(i + 1) % n].unlock();
}



int main() {
    constexpr int NUM_PHILOSOPHERS = 5;

    std::mutex chopstick[NUM_PHILOSOPHERS];
    std::thread lstTh[NUM_PHILOSOPHERS];

    // CREATE THREADS
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        lstTh[i] = std::thread(&doTaskPhilosopher, chopstick, NUM_PHILOSOPHERS, i);
    }

    // JOIN THREADS
    for (auto&& th : lstTh) {
        th.join();
    }

    return 0;
}
