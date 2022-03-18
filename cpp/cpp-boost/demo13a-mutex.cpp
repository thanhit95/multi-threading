/*
MUTEXES
*/


#include <iostream>
#include <boost/chrono.hpp>
#include <boost/thread.hpp>
using namespace std;



boost::mutex mut;
int counter = 0;



void doTask() {
    boost::this_thread::sleep_for(boost::chrono::seconds(1));

    mut.lock();

    for (int i = 0; i < 1000; ++i)
        ++counter;

    mut.unlock();
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
