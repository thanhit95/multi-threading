/*
RACE CONDITIONS AND DATA RACES
*/


#include <iostream>
#include <thread>
#include <chrono>
using namespace std;



int counter = 0;



void increaseCounter() {
    for (int i = 0; i < 500; ++i) {
        std::this_thread::sleep_for(std::chrono::microseconds(3));
        counter += 1;
    }
}



int main() {
    auto thFoo = std::thread(increaseCounter);
    auto thBar = std::thread(increaseCounter);
    auto thEgg = std::thread(increaseCounter);

    thFoo.join();
    thBar.join();
    thEgg.join();

    cout << "counter = " << counter << endl;
    // We are not sure that counter = 1500

    return 0;
}
