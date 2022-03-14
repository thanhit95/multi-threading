/*
MUTEXES

boost::unique_lock is more complex than boost::lock_guard:
Not only does it provide for RAII-style locking, it also allows for
deferring acquiring the lock until the lock() member function is called explicitly,
or trying to acquire the lock in a non-blocking fashion, or with a timeout.

Consequently, unlock() is only called in the destructor if the lock object
has locked the Lockable object, or otherwise adopted a lock on the Lockable object.

(From Boost's docs website)
*/


#include <iostream>
#include <boost/chrono.hpp>
#include <boost/thread.hpp>
using namespace std;



boost::mutex mut;
int counter = 0;



void doTask() {
    boost::this_thread::sleep_for(boost::chrono::seconds(1));

    boost::unique_lock<boost::mutex> lk(mut);

    for (int i = 0; i < 1000; ++i)
        ++counter;
}



int main() {
    const int NUM_THREADS = 16;
    boost::thread_group lstTh;

    for (int i = 0; i < NUM_THREADS; ++i) {
        lstTh.add_thread(new boost::thread(doTask));
    }

    lstTh.join_all();

    cout << "counter = " << counter << endl;
    // We are sure that counter = 16000

    return 0;
}
