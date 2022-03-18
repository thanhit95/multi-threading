/*
THREAD-LOCAL STORAGE
Introduction
    The basic way to use thread-local storage
*/


#include <iostream>
#include <string>
#include <boost/chrono.hpp>
#include <boost/thread.hpp>
using namespace std;



boost::thread_specific_ptr<string> value;



void printLocalValue() {
    cout << (*value.get()) << endl;
}



void doTaskApple() {
    value.reset(new string("APPLE"));
    boost::this_thread::sleep_for(boost::chrono::seconds(2));
    printLocalValue();
}



void doTaskBanana() {
    value.reset(new string("BANANA"));
    boost::this_thread::sleep_for(boost::chrono::seconds(2));
    printLocalValue();
}



int main() {
    boost::thread thApple(&doTaskApple);
    boost::thread thBanana(&doTaskBanana);

    thApple.join();
    thBanana.join();

    return 0;
}
