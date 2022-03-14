/*
DEADLOCK
Version B
*/


#include <iostream>
#include <boost/chrono.hpp>
#include <boost/thread.hpp>
using namespace std;



boost::mutex mutResourceA;
boost::mutex mutResourceB;



void foo() {
    mutResourceA.lock();
    cout << "foo acquired resource A" << endl;

    boost::this_thread::sleep_for(boost::chrono::seconds(1));

    mutResourceB.lock();
    cout << "foo acquired resource B" << endl;
    mutResourceB.unlock();

    mutResourceA.unlock();
}



void bar() {
    mutResourceB.lock();
    cout << "bar acquired resource B" << endl;

    boost::this_thread::sleep_for(boost::chrono::seconds(1));

    mutResourceA.lock();
    cout << "bar acquired resource A" << endl;
    mutResourceA.unlock();

    mutResourceB.unlock();
}



int main() {
    boost::thread thFoo(foo);
    boost::thread thBar(bar);

    thFoo.join();
    thBar.join();

    cout << "You will never see this statement due to deadlock!" << endl;
    return 0;
}
