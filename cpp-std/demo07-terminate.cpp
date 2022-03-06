/*
FORCING A THREAD TO TERMINATE (i.e. killing the thread)
*/


#include <iostream>
#include <chrono>
#include <thread>
using namespace std;



volatile bool isRunning;



void doTask() {
    while (isRunning) {
        cout << "Running..." << endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}



int main() {
    isRunning = true;
    auto th = std::thread(doTask);

    std::this_thread::sleep_for(std::chrono::seconds(6));
    isRunning = false;

    th.join();
    return 0;
}
