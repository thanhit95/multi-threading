/*
REENTRANT LOCKS (RECURSIVE MUTEXES)
Version C: A multithreaded app example
*/


#include <iostream>
#include <boost/chrono.hpp>
#include <boost/thread.hpp>
using namespace std;



boost::recursive_mutex mut;



void doTask(char name) {
    boost::this_thread::sleep_for(boost::chrono::seconds(1));

    mut.lock();
    cout << "First time " << name << " acquiring the resource" << endl;

    mut.lock();
    cout << "Second time " << name << " acquiring the resource" << endl;

    mut.unlock();
    mut.unlock();
}



void doTaskUsingSyncBlock(char name) {
    typedef boost::unique_lock<boost::recursive_mutex> uniquelk;

    boost::this_thread::sleep_for(boost::chrono::seconds(1));

    {
        uniquelk(mut);
        cout << "First time " << name << " acquiring the resource" << endl;

        {
            uniquelk(mut);
            cout << "Second time " << name << " acquiring the resource" << endl;
        }
    }
}



int main() {
    const int NUM_THREADS = 3;
    boost::thread_group lstTh;

    for (int i = 0; i < NUM_THREADS; ++i) {
        lstTh.add_thread(new boost::thread(&doTask, char(i + 'A')));
    }

    lstTh.join_all();

    return 0;
}
