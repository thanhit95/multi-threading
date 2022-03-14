/*
CONDITION VARIABLES
*/


#include <iostream>
#include <boost/chrono.hpp>
#include <boost/thread.hpp>
using namespace std;



boost::mutex mut;
boost::condition_variable conditionVar;

const int NUM_TH_FOO = 3;



void foo() {
    cout << "foo is waiting..." << endl;

    boost::unique_lock<boost::mutex> mutLock(mut);
    conditionVar.wait(mutLock);

    cout << "foo resumed" << endl;
}



void bar() {
    for (int i = 0; i < NUM_TH_FOO; ++i) {
        boost::this_thread::sleep_for(boost::chrono::seconds(2));
        conditionVar.notify_one();
    }
}



int main() {
    boost::thread_group lstThFoo;

    for (int i = 0; i < NUM_TH_FOO; ++i) {
        lstThFoo.add_thread(new boost::thread(foo));
    }

    boost::thread thBar(bar);

    lstThFoo.join_all();
    thBar.join();

    return 0;
}
