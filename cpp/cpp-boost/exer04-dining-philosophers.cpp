/*
THE DINING PHILOSOPHERS PROBLEM
*/


#include <iostream>
#include <boost/chrono.hpp>
#include <boost/thread.hpp>
using namespace std;



void doTaskPhilosopher(boost::mutex chopstick[], int numPhilo, int idPhilo) {
    int n = numPhilo;
    int i = idPhilo;

    boost::this_thread::sleep_for(boost::chrono::seconds(1));

    chopstick[i].lock();
    chopstick[(i + 1) % n].lock();

    cout << "Philosopher #" << i << " is eating the rice" << endl;

    chopstick[i].unlock();
    chopstick[(i + 1) % n].unlock();
}



int main() {
    const int NUM_PHILOSOPHERS = 5;

    boost::mutex chopstick[NUM_PHILOSOPHERS];
    boost::thread_group lstTh;

    // CREATE THREADS
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        lstTh.add_thread(new boost::thread(
            doTaskPhilosopher, chopstick, NUM_PHILOSOPHERS, i
        ));
    }

    // JOIN THREADS
    lstTh.join_all();

    return 0;
}
