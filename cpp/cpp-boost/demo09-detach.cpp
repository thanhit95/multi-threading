/*
THREAD DETACHING
*/


#include <iostream>
#include <boost/chrono.hpp>
#include <boost/thread.hpp>
using namespace std;



void foo() {
    cout << "foo is starting..." << endl;

    boost::this_thread::sleep_for(boost::chrono::seconds(2));

    cout << "foo is exiting..." << endl;
}



int main() {
    boost::thread thFoo(foo);
    thFoo.detach();


    // If I comment this statement,
    // thFoo will be forced into terminating with main thread
    boost::this_thread::sleep_for(boost::chrono::seconds(3));


    cout << "Main thread is exiting" << endl;
    return 0;
}
