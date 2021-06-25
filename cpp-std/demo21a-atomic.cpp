/*
ATOMIC
*/


#include <iostream>
#include <thread>
#include <chrono>
using namespace std;



volatile int counter = 0;



void routine() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    counter += 1;
}



int main() {
    auto thA = std::thread(routine);
    auto thB = std::thread(routine);

    thA.join();
    thB.join();

    cout << "counter = " << counter << endl; // unpredictable result
    return 0;
}
