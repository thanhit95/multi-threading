/*
FORCING A THREAD TO TERMINATE
(i.e. killing the thread)
*/


#include <iostream>
#include <thread>
#include <atomic>
using namespace std;



std::atomic_bool flagStop;



void routine() {
    cout << "Running..." << endl;

    while (1) {
        if (flagStop.load())
            break;

        std::this_thread::sleep_for(std::chrono::microseconds(500));
    }

    cout << "Done" << endl;
}



int main() {
    flagStop.store(false);

    auto th = std::thread(routine);

    std::this_thread::sleep_for(std::chrono::seconds(3));

    flagStop.store(true);

    th.join();
    return 0;
}
