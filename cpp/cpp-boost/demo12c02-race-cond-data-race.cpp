/*
RACE CONDITIONS AND DATA RACES
*/


#include <iostream>
#include <boost/chrono.hpp>
#include <boost/thread.hpp>
using namespace std;



typedef boost::chrono::system_clock sysclock;



int counter = 0;



void doTaskA(sysclock::time_point timePointWakeUp) {
    boost::this_thread::sleep_until(timePointWakeUp);

    while (counter < 10)
        ++counter;

    cout << "A won !!!" << endl;
}



void doTaskB(sysclock::time_point timePointWakeUp) {
    boost::this_thread::sleep_until(timePointWakeUp);

    while (counter > -10)
        --counter;

    cout << "B won !!!" << endl;
}



int main() {
    sysclock::time_point tpNow = sysclock::now();
    sysclock::time_point tpWakeUp = tpNow + boost::chrono::seconds(1);

    boost::thread thA(doTaskA, tpWakeUp);
    boost::thread thB(doTaskB, tpWakeUp);

    thA.join();
    thB.join();

    return 0;
}
