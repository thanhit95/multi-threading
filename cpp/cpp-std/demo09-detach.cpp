/*
THREAD DETACHING
*/


#include <iostream>
#include <chrono>
#include <thread>
using namespace std;



void foo() {
    cout << "foo is starting..." << endl;

    std::this_thread::sleep_for(std::chrono::seconds(2));

    cout << "foo is exiting..." << endl;
}



int main() {
    auto thFoo = std::thread(&foo);
    thFoo.detach();


    // If I comment this statement,
    // thFoo will be forced into terminating with main thread
    std::this_thread::sleep_for(std::chrono::seconds(3));


    cout << "Main thread is exiting" << endl;
    return 0;
}
