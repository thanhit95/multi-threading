/*
SYNCHRONIZED BLOCKS

Synchronized blocks in C++ Boost threading are not supported by default.
To demonstate synchronized blocks, I use boost::unique_lock (or boost::lock_guard).

Now, let's see the code:
    {
        boost::unique_lock lk(mut);
        // Do something in the critical section
    }

The code block above is protected by a lock/mutex. That means it is synchronized on thread execution.
This code block is called "the synchronized block".
*/


#include <iostream>
#include <boost/chrono.hpp>
#include <boost/thread.hpp>
using namespace std;



boost::mutex mut;
int counter = 0;



void doTask() {
    boost::this_thread::sleep_for(boost::chrono::seconds(1));

    // This is the "synchronized block"
    {
        boost::unique_lock<boost::mutex> lk(mut);

        for (int i = 0; i < 1000; ++i)
            ++counter;
    }
}



int main() {
    const int NUM_THREADS = 16;
    boost::thread_group lstTh;

    for (int i = 0; i < NUM_THREADS; ++i) {
        lstTh.add_thread(new boost::thread(&doTask));
    }

    lstTh.join_all();

    cout << "counter = " << counter << endl;
    // We are sure that counter = 16000

    return 0;
}
