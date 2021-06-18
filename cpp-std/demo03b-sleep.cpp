#include <iostream>
#include <string>
#include <thread>
#include <chrono>

using namespace std;



using sysclock = std::chrono::system_clock;



char* getStrTimePoint(sysclock::time_point tp) {
    std::time_t timeStamp = sysclock::to_time_t(tp);
    return std::ctime(&timeStamp);
}



void routine(string name, sysclock::time_point tpWakeUp) {
    std::this_thread::sleep_until(tpWakeUp);
    cout << name << " wakes up" << endl;
}



int main() {
    auto tpNow = sysclock::now();
    auto tpWakeUpFoo = tpNow + std::chrono::seconds(7);
    auto tpWakeUpBar = tpNow + std::chrono::seconds(3);

    cout << "foo will sleep until " << getStrTimePoint(tpWakeUpFoo) << endl;
    cout << "bar will sleep until " << getStrTimePoint(tpWakeUpBar) << endl;

    auto thFoo = std::thread(routine, "foo", tpWakeUpFoo);
    auto thBar = std::thread(routine, "bar", tpWakeUpBar);

    thFoo.join();
    thBar.join();

    return 0;
}
