/*
SLEEP
Version B: Sleep until a specific time point
*/


#include <iostream>
#include <string>
#include <boost/chrono.hpp>
#include <boost/thread.hpp>
#include "mylib-time.hpp"
using namespace std;



typedef boost::chrono::system_clock sysclock;



void doTask(string name, sysclock::time_point tpWakeUp) {
    boost::this_thread::sleep_until(tpWakeUp);
    cout << name << " wakes up" << endl;
}



int main() {
    sysclock::time_point tpNow = sysclock::now();
    sysclock::time_point tpWakeUpFoo = tpNow + boost::chrono::seconds(7);
    sysclock::time_point tpWakeUpBar = tpNow + boost::chrono::seconds(3);

    cout << "foo will sleep until " << mylib::getTimePointStr(tpWakeUpFoo) << endl;
    cout << "bar will sleep until " << mylib::getTimePointStr(tpWakeUpBar) << endl;

    boost::thread thFoo(doTask, "foo", tpWakeUpFoo);
    boost::thread thBar(doTask, "bar", tpWakeUpBar);

    thFoo.join();
    thBar.join();

    return 0;
}
