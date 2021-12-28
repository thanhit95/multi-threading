/*
SLEEP
Version A: Sleep for a specific duration
*/


#include <iostream>
#include <string>
#include <thread>
#include <chrono>
using namespace std;



void routine(string name) {
    cout << name << " is sleeping" << endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    cout << name << " wakes up" << endl;
}



int main() {
    auto th1 = std::thread(routine, "foo");
    auto th2 = std::thread(routine, "bar");

    th1.join();
    th2.join();

    return 0;
}
