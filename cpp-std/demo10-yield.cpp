/*
THREAD YIELDING
*/


#include <iostream>
#include <thread>
#include <chrono>
#include "mylib-time.hpp"
using namespace std;



using chrmicro = std::chrono::microseconds;
using hrclock = mylib::HiResClock;



void littleSleep(int us) {
    auto tpStart = hrclock::now();
    auto tpEnd = tpStart + chrmicro(us);

    do {
        std::this_thread::yield();
    }
    while (hrclock::now() < tpEnd);
}



int main() {
    auto tpStartMeasure = hrclock::now();

    littleSleep(130);

    auto timeElapsed = hrclock::getTimeSpan<chrmicro>(tpStartMeasure);

    cout << "Elapsed time: " << timeElapsed.count() << " microseonds" << endl;
    return 0;
}
