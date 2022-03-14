/*
ATOMIC ACCESS
*/


#include <iostream>
#include <boost/chrono.hpp>
#include <boost/thread.hpp>
using namespace std;



// boost::atomic<int> counter;
boost::atomic_int32_t counter;



void doTask() {
    boost::this_thread::sleep_for(boost::chrono::seconds(1));
    counter += 1;
}



int main() {
    counter = 0;

    boost::thread_group lstTh;

    for (int i = 0; i < 1000; ++i) {
        lstTh.add_thread(new boost::thread(doTask));
    }

    lstTh.join_all();

    // counter = 1000
    cout << "counter = " << counter << endl;
    return 0;
}
