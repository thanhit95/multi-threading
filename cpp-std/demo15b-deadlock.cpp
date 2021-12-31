/*
DEADLOCK
Version B
*/


#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std;



std::mutex mutResourceA;
std::mutex mutResourceB;



void foo() {
    mutResourceA.lock();
    cout << "foo acquired resource A" << endl;

    std::this_thread::sleep_for(std::chrono::seconds(1));

    mutResourceB.lock();
    cout << "foo acquired resource B" << endl;
    mutResourceB.unlock();

    mutResourceA.unlock();
}



void bar() {
    mutResourceB.lock();
    cout << "bar acquired resource B" << endl;

    std::this_thread::sleep_for(std::chrono::seconds(1));

    mutResourceA.lock();
    cout << "bar acquired resource A" << endl;
    mutResourceA.unlock();

    mutResourceB.unlock();
}



int main() {
    auto thFoo = std::thread(foo);
    auto thBar = std::thread(bar);

    thFoo.join();
    thBar.join();

    cout << "You will never see this statement due to deadlock!" << endl;
    return 0;
}
