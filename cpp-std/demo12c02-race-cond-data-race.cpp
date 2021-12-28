/*
RACE CONDITIONS AND DATA RACES
*/


#include <iostream>
#include <thread>
#include <chrono>
using namespace std;



using sysclock = std::chrono::system_clock;



int counter = 0;



void routineA(sysclock::time_point timePointWakeUp) {
    std::this_thread::sleep_until(timePointWakeUp);

    while (counter < 10)
        ++counter;

    cout << "A won !!!" << endl;
}



void routineB(sysclock::time_point timePointWakeUp) {
    std::this_thread::sleep_until(timePointWakeUp);

    while (counter > -10)
        --counter;

    cout << "B won !!!" << endl;
}



int main() {
    auto tpNow = sysclock::now();
    auto tpWakeUp = tpNow + std::chrono::seconds(2);

    auto thA = std::thread(routineA, tpWakeUp);
    auto thB = std::thread(routineB, tpWakeUp);

    thA.join();
    thB.join();

    return 0;
}
