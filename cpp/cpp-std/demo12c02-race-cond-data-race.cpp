/*
RACE CONDITIONS AND DATA RACES
*/


#include <iostream>
#include <chrono>
#include <thread>
using namespace std;



using sysclock = std::chrono::system_clock;



int counter = 0;



void doTaskA(sysclock::time_point timePointWakeUp) {
    std::this_thread::sleep_until(timePointWakeUp);

    while (counter < 10)
        ++counter;

    cout << "A won !!!" << endl;
}



void doTaskB(sysclock::time_point timePointWakeUp) {
    std::this_thread::sleep_until(timePointWakeUp);

    while (counter > -10)
        --counter;

    cout << "B won !!!" << endl;
}



int main() {
    auto tpNow = sysclock::now();
    auto tpWakeUp = tpNow + std::chrono::seconds(1);

    auto thA = std::thread(&doTaskA, tpWakeUp);
    auto thB = std::thread(&doTaskB, tpWakeUp);

    thA.join();
    thB.join();

    return 0;
}
