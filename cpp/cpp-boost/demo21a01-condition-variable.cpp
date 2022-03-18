/*
CONDITION VARIABLES
*/


#include <iostream>
#include <boost/chrono.hpp>
#include <boost/thread.hpp>
using namespace std;



boost::mutex mut;
boost::condition_variable conditionVar;



void foo() {
    cout << "foo is waiting..." << endl;

    boost::unique_lock<boost::mutex> mutLock(mut);
    conditionVar.wait(mutLock);

    cout << "foo resumed" << endl;
}



void bar() {
    boost::this_thread::sleep_for(boost::chrono::seconds(3));
    conditionVar.notify_one();
}



int main() {
    boost::thread thFoo(&foo);
    boost::thread thBar(&bar);

    thFoo.join();
    thBar.join();

    return 0;
}
