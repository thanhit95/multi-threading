/*
YIELD
*/


#include <iostream>
#include <thread>
#include <chrono>
#include "mytool-time.hpp"
using namespace std;



void littleSleep(int us) {
    auto tpStart = mytool::HiResClock::now();
    auto tpEnd = tpStart + std::chrono::microseconds(us);

    int ret = 0;

    do {
        ret = pthread_yield();
    }
    while (mytool::HiResClock::now() < tpEnd);
}



int main() {
    auto tpStartMeasure = mytool::HiResClock::now();


    littleSleep(130);


    auto timeElapsed = mytool::HiResClock::getTimeSpan<chrono::microseconds>(tpStartMeasure);


    cout << "Elapsed time: " << timeElapsed.count() << " microseonds" << endl;


    return 0;
}
