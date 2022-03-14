/*
FORCING A THREAD TO TERMINATE (i.e. killing the thread)
*/


#include <iostream>
#include <boost/chrono.hpp>
#include <boost/thread.hpp>
using namespace std;



volatile bool isRunning;



void doTask() {
    while (isRunning) {
        cout << "Running..." << endl;
        boost::this_thread::sleep_for(boost::chrono::seconds(2));
    }
}



int main() {
    isRunning = true;
    boost::thread th(doTask);

    boost::this_thread::sleep_for(boost::chrono::seconds(6));
    isRunning = false;

    th.join();
    return 0;
}
