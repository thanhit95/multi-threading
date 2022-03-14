/*
LIST OF MULTIPLE THREADS
Version A: Using standard arrays
*/


#include <iostream>
#include <boost/thread.hpp>
using namespace std;



void doTask(int index) {
    cout << index;
}



int main() {
    const int NUM_THREADS = 5;

    boost::thread lstTh[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; ++i) {
        lstTh[i] = boost::thread(doTask, i);
    }

    for (int i = 0; i < NUM_THREADS; ++i) {
        lstTh[i].join();
    }

    cout << endl;
    return 0;
}
