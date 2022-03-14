/*
RACE CONDITIONS AND DATA RACES
*/


#include <iostream>
#include <boost/chrono.hpp>
#include <boost/thread.hpp>
using namespace std;



int counter = 0;



void increaseCounter() {
    boost::this_thread::sleep_for(boost::chrono::seconds(1));

    for (int i = 0; i < 1000; ++i) {
        counter += 1;
    }
}



int main() {
    const int NUM_THREADS = 16;
    boost::thread_group lstTh;

    for (int i = 0; i < NUM_THREADS; ++i) {
        lstTh.add_thread(new boost::thread(increaseCounter));
    }

    lstTh.join_all();

    cout << "counter = " << counter << endl;
    // We are NOT sure that counter = 16000

    return 0;
}
