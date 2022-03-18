/*
CONDITION VARIABLES
*/


#include <iostream>
#include <boost/chrono.hpp>
#include <boost/thread.hpp>
using namespace std;



boost::mutex mut;
boost::condition_variable conditionVar;

int counter = 0;

const int COUNT_HALT_01 = 3;
const int COUNT_HALT_02 = 6;
const int COUNT_DONE = 10;



// Write numbers 1-3 and 8-10 as permitted by egg()
void foo() {
    for (;;) {
        // Lock mutex and then wait for signal to relase mutex
        boost::unique_lock<boost::mutex> lk(mut);

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
        boost::unique_lock<boost::mutex> lk(mut);

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
    boost::thread thFoo(&foo);
    boost::thread thEgg(&egg);

    thFoo.join();
    thEgg.join();

    return 0;
}
