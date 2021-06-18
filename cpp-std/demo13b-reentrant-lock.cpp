/*
REENTRANT LOCK (RECURSIVE MUTEX)

The reason for using Reentrant Lock is to avoid a deadlock due to e.g. recursion.

A reentrant lock is a synchronization primitive that may be acquired multiple times by the same thread.
Internally, it uses the concepts of "owning thread" and "recursion level" in addition to
the locked/unlocked state used by primitive locks.
In the locked state, some thread owns the lock; in the unlocked state, no thread owns it.
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
