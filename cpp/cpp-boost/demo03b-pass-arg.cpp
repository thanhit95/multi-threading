/*
PASSING ARGUMENTS
Version B: Passing constant references
*/


#include <iostream>
#include <string>
#include <boost/thread.hpp>
using namespace std;



void doTask(const string& msg) {
    cout << msg << endl;
}

void doTask(const string& msg) {
    cout << msg << endl;
}



int main() {
    boost::thread thFoo(doTask, "foo");
    boost::thread thBar(doTask, "bar");

    thFoo.join();
    thBar.join();

    return 0;
}
