/*
LIST OF MULTIPLE THREADS
Version B: Using the std::vector
*/


#include <iostream>
#include <boost/bind/bind.hpp>
#include <boost/thread.hpp>
using namespace std;



void doTask(int index) {
    cout << index;
}



int main() {
    const int NUM_THREADS = 5;

    boost::thread_group lstTh;

    for (int i = 0; i < NUM_THREADS; ++i) {
        lstTh.add_thread(new boost::thread(doTask, i));
        // lstTh.create_thread(boost::bind(doTask, i));
    }

    lstTh.join_all();

    cout << endl;
    return 0;
}
