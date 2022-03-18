/*
THREAD-LOCAL STORAGE
Avoiding synchronization using thread-local storage
*/


#include <iostream>
#include <boost/chrono.hpp>
#include <boost/thread.hpp>
using namespace std;



boost::thread_specific_ptr<int> counter;



void doTask(int t) {
    boost::this_thread::sleep_for(boost::chrono::seconds(1));
    counter.reset(new int(0));

    for (int i = 0; i < 1000; ++i)
        (*counter) += 1;

    cout << "Thread " << t << " gives counter = " << (*counter) << endl;
}



int main() {
    const int NUM_THREADS = 3;
    boost::thread_group lstTh;

    for (int i = 0; i < NUM_THREADS; ++i) {
        lstTh.add_thread(new boost::thread(&doTask, i));
    }

    lstTh.join_all();

    cout << endl;

    /*
    By using thread-local storage, each thread has its own counter.
    So, the counter in one thread is completely independent of each other.

    Thread-local storage helps us to AVOID SYNCHRONIZATION.
    */
    return 0;
}
