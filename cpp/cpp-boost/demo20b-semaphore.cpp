/*
SEMAPHORES
Version B: Tires and chassis

Semaphores in C++ Boost threading are not supported by default.
So, I use mylib::Semaphore for this demonstration.
*/


#include <iostream>
#include <boost/chrono.hpp>
#include <boost/thread.hpp>
#include "mylib-semaphore.hpp"
using namespace std;



mylib::Semaphore semTire(4);
mylib::Semaphore semChassis(0);



void makeTire() {
    for (int i = 0; i < 8; ++i) {
        semTire.acquire();

        cout << "Make 1 tire" << endl;
        boost::this_thread::sleep_for(boost::chrono::seconds(1));

        semChassis.release();
    }
}



void makeChassis() {
    for (int i = 0; i < 4; ++i) {
        semChassis.acquire();
        semChassis.acquire();
        semChassis.acquire();
        semChassis.acquire();

        cout << "Make 1 chassis" << endl;
        boost::this_thread::sleep_for(boost::chrono::seconds(3));

        semTire.release();
        semTire.release();
        semTire.release();
        semTire.release();
    }
}



int main() {
    boost::thread thTireA(makeTire);
    boost::thread thTireB(makeTire);
    boost::thread thChassis(makeChassis);

    thTireA.join();
    thTireB.join();
    thChassis.join();

    return 0;
}
