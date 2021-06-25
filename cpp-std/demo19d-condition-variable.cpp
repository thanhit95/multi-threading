/*
CONDITION VARIABLE
*/


#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
using namespace std;



std::mutex mut;

std::condition_variable conditionVar;

int counter = 0;

constexpr int COUNT_HALT_01 = 3;
constexpr int COUNT_HALT_02 = 6;
constexpr int COUNT_DONE = 10;



// Write numbers 1-3 and 8-10 as permitted by eggs()
void foo() {
    for (;;) {
        // Lock mutex and then wait for signal to relase mutex
        std::unique_lock<std::mutex> mutLock(mut);

        // Wait while eggs() operates on counter,
        // Mutex unlocked if condition variable in eggs() signaled
        conditionVar.wait(mutLock);

        ++counter;
        cout << "foo counter = " << counter << endl;

        if (counter >= COUNT_DONE) {
            return;
        }
    }
}



// Write numbers 4-7
void eggs() {
    for (;;) {
        if (counter < COUNT_HALT_01 || counter > COUNT_HALT_02) {
            // Signal to free waiting thread by freeing the mutex
            // Note: foo() is now permitted to modify "counter"
            conditionVar.notify_one();
        }
        else {
            mut.lock();
            ++counter;
            cout << "eggs counter = " << counter << endl;
            mut.unlock();
        }

        if (counter >= COUNT_DONE) {
            return;
        }
    }
}



int main() {
    auto thFoo = std::thread(foo);
    auto thEggs = std::thread(eggs);

    thFoo.join();
    thEggs.join();

    return 0;
}
