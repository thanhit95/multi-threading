/*
SLEEP
Version B: Sleep until a specific time point
*/


#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include "mylib-time.hpp"
using namespace std;



using sysclock = std::chrono::system_clock;



void doTask(string name, sysclock::time_point tpWakeUp) {
    std::this_thread::sleep_until(tpWakeUp);
    cout << name << " wakes up" << endl;
}



int main() {
    auto tpNow = sysclock::now();
    auto tpWakeUpFoo = tpNow + std::chrono::seconds(7);
    auto tpWakeUpBar = tpNow + std::chrono::seconds(3);

    cout << "foo will sleep until " << mylib::getTimePointStr(tpWakeUpFoo) << endl;
    cout << "bar will sleep until " << mylib::getTimePointStr(tpWakeUpBar) << endl;

    auto thFoo = std::thread(&doTask, "foo", tpWakeUpFoo);
    auto thBar = std::thread(&doTask, "bar", tpWakeUpBar);

    thFoo.join();
    thBar.join();

    return 0;
}
