/*
THREAD-LOCAL STORAGE
Introduction

The basic way to use thread-local storage
*/


#include <iostream>
#include <string>
#include <thread>
using namespace std;



thread_local string value = "NOT SET";



void routine() {
    cout << value << endl;
}



int main() {
    // Main thread sets value = "APPLE"
    value = "APPLE";
    cout << value << endl;

    // Child thread gets value
    // Expected output: "NOT SET"
    auto th = std::thread(routine);
    th.join();

    return 0;
}
