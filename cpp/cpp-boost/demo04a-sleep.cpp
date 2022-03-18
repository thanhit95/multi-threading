/*
SLEEP
Version A: Sleep for a specific duration
*/


#include <iostream>
#include <string>
#include <boost/chrono.hpp>
#include <boost/thread.hpp>
using namespace std;



void doTask(string name) {
    cout << name << " is sleeping" << endl;
    boost::this_thread::sleep_for(boost::chrono::seconds(3));
    cout << name << " wakes up" << endl;
}



int main() {
    boost::thread thFoo(&doTask, "foo");

    thFoo.join();

    cout << "Good bye" << endl;
    return 0;
}
