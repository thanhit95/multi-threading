/*
CONDITION VARIABLES
*/


#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <condition_variable>
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
    conditionVar.notify_one();
}



int main() {
    auto thFoo = std::thread(foo);
    auto thBar = std::thread(bar);

    thFoo.join();
    thBar.join();

    return 0;
}
