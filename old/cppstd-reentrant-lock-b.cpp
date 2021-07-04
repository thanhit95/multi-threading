/*
REENTRANT LOCK (RECURSIVE MUTEX)
*/


#include <iostream>
#include <thread>
#include <mutex>
using namespace std;



std::recursive_mutex mut;



int getFactorial(int n) {
    if (n <= 0)
        return 1;

    mut.lock();

    int result = n * getFactorial(n - 1);

    mut.unlock();

    return result;
}



void routine(int n) {
    int factorial = getFactorial(n);
    cout << "Factorial of " << n << " is " << factorial << endl;
}



int main() {
    int n = 5;

    auto th = std::thread(routine, n);

    th.join();

    return 0;
}
