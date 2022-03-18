/*
RACE CONDITIONS
*/


#include <iostream>
#include <boost/chrono.hpp>
#include <boost/thread.hpp>
using namespace std;



void doTask(int index) {
    boost::this_thread::sleep_for(boost::chrono::seconds(1));
    cout << index;
}



int main() {
    const int NUM_THREADS = 4;
    boost::thread_group lstTh;

    for (int i = 0; i < NUM_THREADS; ++i) {
        lstTh.add_thread(new boost::thread(&doTask, i));
    }

    lstTh.join_all();

    cout << endl;
    return 0;
}
