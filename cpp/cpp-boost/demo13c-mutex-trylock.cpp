/*
MUTEXES
Locking with a nonblocking mutex
*/


#include <iostream>
#include <boost/chrono.hpp>
#include <boost/thread.hpp>
using namespace std;



boost::mutex mut;
int counter = 0;



void doTask() {
    boost::this_thread::sleep_for(boost::chrono::seconds(1));

    if (false == mut.try_lock()) {
        return;
    }

    for (int i = 0; i < 10000; ++i)
        ++counter;

    mut.unlock();
}



int main() {
    const int NUM_THREADS = 3;
    boost::thread_group lstTh;

    for (int i = 0; i < NUM_THREADS; ++i) {
        lstTh.add_thread(new boost::thread(doTask));
    }

    lstTh.join_all();

    cout << "counter = " << counter << endl;
    // counter can be 10000, 20000 or 30000

    return 0;
}
