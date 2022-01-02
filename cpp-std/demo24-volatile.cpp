/*
THE VOLATILE KEYWORD
*/


#include <iostream>
#include <chrono>
#include <thread>
using namespace std;



volatile bool stopped = false;



void doTask() {
    while (false == stopped) {
        cout << "Running..." << endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}



int main() {
    auto th = std::thread(doTask);

    std::this_thread::sleep_for(std::chrono::seconds(6));

    stopped = true;

    th.join();

    return 0;
}
