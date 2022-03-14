/*
MAXIMUM NUMBER OF DIVISORS
*/


#include <iostream>
#include "../cpp-std/mylib-time.hpp"
using namespace std;



int main() {
    constexpr int RANGE_START = 1;
    constexpr int RANGE_END = 100000;

    int resValue = 0;
    int resNumDiv = 0;  // number of divisors of result

    auto tpStart = mylib::HiResClock::now();


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


    auto timeElapsed = mylib::HiResClock::getTimeSpan(tpStart);

    cout << "The integer which has largest number of divisors is " << resValue << endl;
    cout << "The largest number of divisor is " << resNumDiv << endl;
    cout << "Time elapsed = " << timeElapsed.count() << endl;

    return 0;
}
