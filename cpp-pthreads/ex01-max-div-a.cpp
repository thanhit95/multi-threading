/*
PROBLEM: Find the integer in the range 1 to 10000 that has the largest number of divisors.

This source code file contains the solution without using multi threads.
*/

#include <iostream>
using namespace std;

int main() {
    int resInt = 0;
    int resNumDiv = 0;  // number of divisors of result

    for (int i = 1; i <= 10000; ++i) {
        int countNumDiv = 0;

        for (int j = 1; j <= i; ++j)
            if (i % j == 0)
                ++countNumDiv;

        if (resNumDiv < countNumDiv) {
            resNumDiv = countNumDiv;
            resInt = i;
        }
    }

    cout << "The integer which has largest number of divisors is " << resInt << endl;
    cout << "The largest number of divisor is " << resNumDiv << endl;

    return 0;
}
