/*
READ-WRITE LOCKS
*/


#include <iostream>
#include <numeric>
#include <boost/chrono.hpp>
#include <boost/thread.hpp>
#include "mylib-random.hpp"
using namespace std;



volatile int resource = 0;
boost::shared_mutex rwmut;



void readFunc(int timeWait) {
    boost::this_thread::sleep_for(boost::chrono::seconds(timeWait));

    boost::shared_lock<boost::shared_mutex> lk(rwmut);

    cout << "read: " << resource << endl;

    // lk.unlock();
}



void writeFunc(int timeWait) {
    boost::this_thread::sleep_for(boost::chrono::seconds(timeWait));

    boost::lock_guard<boost::shared_mutex> lk(rwmut);
    // boost::unique_lock<boost::shared_mutex> lk(rwmut);

    resource = mylib::RandInt::get(100);
    cout << "write: " << resource << endl;

    // lk.unlock();
}



int main() {
    const int NUM_THREADS_READ = 10;
    const int NUM_THREADS_WRITE = 4;
    const int NUM_ARGS = 3;

    boost::thread_group lstThRead;
    boost::thread_group lstThWrite;
    int lstArg[NUM_ARGS];


    // INITIALIZE
    for (int i = 0; i < NUM_ARGS; ++i) {
        lstArg[i] = i;
    }


    // CREATE THREADS
    for (int i = 0; i < NUM_THREADS_READ; ++i) {
        int arg = lstArg[ mylib::RandInt::get(NUM_ARGS) ];

        lstThRead.add_thread(new boost::thread(
            &readFunc, arg
        ));
    }

    for (int i = 0; i < NUM_THREADS_WRITE; ++i) {
        int arg = lstArg[ mylib::RandInt::get(NUM_ARGS) ];

        lstThWrite.add_thread(new boost::thread(
            &writeFunc, arg
        ));
    }


    // JOIN THREADS
    lstThRead.join_all();
    lstThWrite.join_all();


    return 0;
}
