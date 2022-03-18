/*
HELLO WORLD VERSION MULTITHREADING
Version A01: Using functions
*/


#include <iostream>
#include <boost/thread.hpp>
using namespace std;



void doTask() {
    cout << "Hello from example thread" << endl;
}



int main() {
    boost::thread th(&doTask);

    cout << "Hello from main thread" << endl;

    th.join();
    return 0;
}
