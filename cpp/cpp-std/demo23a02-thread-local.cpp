/*
THREAD-LOCAL STORAGE
Introduction
    The smart-pointer way to use thread-local storage
*/


#include <iostream>
#include <string>
#include <memory>
#include <thread>
using namespace std;



thread_local std::shared_ptr<string> value;



string getValue() {
    if (nullptr == value.get()) {
        value.reset(new string("NOT SET"));
    }

    return *value.get();
}



void doTask() {
    cout << getValue() << endl;
}



int main() {
    // Main thread sets value = "APPLE"
    value.reset(new string("APPLE"));
    cout << getValue() << endl;

    // Child thread gets value
    // Expected output: "NOT SET"
    auto th = std::thread(&doTask);
    th.join();

    return 0;
}
