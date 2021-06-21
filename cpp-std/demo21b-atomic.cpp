#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>
using namespace std;



std::atomic_int32_t counter;



void routine() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    counter += 1;
}



int main() {
    counter = 0;

    auto thA = std::thread(routine);
    auto thB = std::thread(routine);

    thA.join();
    thB.join();

    cout << "counter = " << counter << endl; // counter = 2
    return 0;
}
