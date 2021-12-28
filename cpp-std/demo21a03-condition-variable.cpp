/*
CONDITION VARIABLES
*/


#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
using namespace std;



std::mutex mut;
std::condition_variable conditionVar;



void foo() {
    cout << "foo is waiting..." << endl;

    std::unique_lock<std::mutex> mutLock(mut);
    conditionVar.wait(mutLock);

    cout << "foo resumed" << endl;
}



void bar() {
    std::this_thread::sleep_for(std::chrono::seconds(3));
    // Notify all waiting threads
    conditionVar.notify_all();
}



int main() {
    constexpr int NUM_TH_FOO = 3;
    std::thread lstThFoo[NUM_TH_FOO];


    for (auto&& th : lstThFoo) {
        th = std::thread(foo);
    }

    auto thBar = std::thread(bar);


    thBar.join();

    for (auto&& th : lstThFoo) {
        th.join();
    }

    return 0;
}
