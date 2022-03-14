/*
MAXIMUM NUMBER OF DIVISORS
*/


#include <iostream>
#include "mylib-time.hpp"
using namespace std;



typedef boost::chrono::microseconds chrmicro;
typedef boost::chrono::steady_clock::time_point time_point;
typedef mylib::HiResClock hrclock;



int main() {
    const int RANGE_START = 1;
    const int RANGE_END = 100000;

    int resValue = 0;
    int resNumDiv = 0;  // number of divisors of result

    time_point tpStart = hrclock::now();


    for (int i = RANGE_START; i <= RANGE_END; ++i) {
        int numDiv = 0;

        for (int j = i / 2; j > 0; --j)
            if (i % j == 0)
                ++numDiv;

        if (resNumDiv < numDiv) {
            resNumDiv = numDiv;
            resValue = i;
        }
    }


    chrmicro timeElapsed = hrclock::getTimeSpan<chrmicro>(tpStart);

    cout << "The integer which has largest number of divisors is " << resValue << endl;
    cout << "The largest number of divisor is " << resNumDiv << endl;
    cout << "Time elapsed = " << (timeElapsed.count() / 1000000.0) << endl;

    return 0;
}
