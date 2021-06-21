#include <iostream>
#include <thread>
#include <chrono>
using namespace std;



volatile int stopped = false;



void routine() {
    while (false == stopped) {
        cout << "Running..." << endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}



int main() {
    auto th = std::thread(routine);

    std::this_thread::sleep_for(std::chrono::seconds(6));

    stopped = true;

    th.join();

    return 0;
}
