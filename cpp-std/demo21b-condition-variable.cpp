/*
CONDITION VARIABLES
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



// Write numbers 1-3 and 8-10 as permitted by egg()
void foo() {
    for (;;) {
        // Lock mutex and then wait for signal to relase mutex
        std::unique_lock<std::mutex> lk(mut);

        // Wait while egg() operates on counter,
        // Mutex unlocked if condition variable in egg() signaled
        conditionVar.wait(lk);

        ++counter;
        cout << "foo counter = " << counter << endl;

        if (counter >= COUNT_DONE) {
            return;
        }
    }
}



// Write numbers 4-7
void egg() {
    for (;;) {
        std::unique_lock<std::mutex> lk(mut);

        if (counter < COUNT_HALT_01 || counter > COUNT_HALT_02) {
            // Signal to free waiting thread by freeing the mutex
            // Note: foo() is now permitted to modify "counter"
            conditionVar.notify_one();
        }
        else {
            ++counter;
            cout << "egg counter = " << counter << endl;
        }

        if (counter >= COUNT_DONE) {
            return;
        }
    }
}



int main() {
    auto thFoo = std::thread(foo);
    auto thEgg = std::thread(egg);

    thFoo.join();
    thEgg.join();

    return 0;
}
