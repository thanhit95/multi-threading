/*
THREAD YIELDING
*/


#include <iostream>
#include <boost/chrono.hpp>
#include <boost/thread.hpp>
#include "mylib-time.hpp"
using namespace std;



typedef boost::chrono::microseconds chrmicro;
typedef boost::chrono::steady_clock::time_point time_point;
typedef mylib::HiResClock hrclock;



void littleSleep(int us) {
    time_point tpStart = hrclock::now();
    time_point tpEnd = tpStart + chrmicro(us);

    do {
        boost::this_thread::yield();
    }
    while (hrclock::now() < tpEnd);
}



int main() {
    time_point tpStartMeasure = hrclock::now();

    littleSleep(130);

    chrmicro timeElapsed = hrclock::getTimeSpan<chrmicro>(tpStartMeasure);

    cout << "Elapsed time: " << timeElapsed.count() << " microseonds" << endl;
    return 0;
}
