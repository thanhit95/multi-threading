/*
SLEEP
Version A: Sleep for a specific duration
*/


#include <iostream>
#include <string>
#include <thread>
#include <chrono>
using namespace std;



void doTask(string name) {
    cout << name << " is sleeping" << endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
    cout << name << " wakes up" << endl;
}



int main() {
    auto thFoo = std::thread(doTask, "foo");

    thFoo.join();

    cout << "Good bye" << endl;
    return 0;
}
