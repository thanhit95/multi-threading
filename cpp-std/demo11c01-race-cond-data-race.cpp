/*
RACE CONDITION AND DATA RACE
*/


#include <iostream>
#include <thread>
#include <chrono>
using namespace std;



int counter = 0;



void foo() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    counter += 1;
}



void bar() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    counter += 2;
}



int main() {
    auto thFoo = std::thread(foo);
    auto thBar = std::thread(bar);

    thFoo.join();
    thBar.join();

    cout << "counter = " << counter << endl;
    /*
    counter can be 1, 2 or 3
    */

    return 0;
}
