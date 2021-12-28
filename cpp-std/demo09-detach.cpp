/*
DETACH
*/


#include <iostream>
#include <thread>
#include <chrono>
using namespace std;



void routine() {
    cout << "Routine is starting..." << endl;

    std::this_thread::sleep_for(std::chrono::seconds(2));

    cout << "Routine is exiting..." << endl;
}



int main() {
    auto th = std::thread(routine);
    th.detach();


    // If I comment this statement,
    // the thread routine will be forced into terminating with main thread
    std::this_thread::sleep_for(std::chrono::seconds(3));


    cout << "Program is terminating" << endl;
    return 0;
}
