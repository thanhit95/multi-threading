/*
DEADLOCK
Version A
*/


#include <iostream>
#include <string>
#include <boost/thread.hpp>
using namespace std;



boost::mutex mut;



void doTask(std::string name) {
    mut.lock();

    cout << name << " acquired resource" << endl;

    // mut.unlock(); // Forget this statement ==> deadlock
}



int main() {
    boost::thread thFoo(doTask, "foo");
    boost::thread thBar(doTask, "bar");

    thFoo.join();
    thBar.join();

    cout << "You will never see this statement due to deadlock!" << endl;
    return 0;
}
