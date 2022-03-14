/*
INTRODUCTION TO MULTITHREADING
You should try running this app several times and see results.
*/


#include <iostream>
#include <boost/thread.hpp>
using namespace std;



void doTask() {
    for (int i = 0; i < 300; ++i)
        cout << "B";
}



int main() {
    boost::thread th(doTask);

    for (int i = 0; i < 300; ++i)
        cout << "A";

    th.join();

    cout << endl;
    return 0;
}
