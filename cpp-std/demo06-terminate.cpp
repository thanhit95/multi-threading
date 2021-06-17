/*
FORCE A THREAD TO TERMINATE
(i.e. kill the thread)
*/


#include <iostream>
#include <thread>
#include <atomic>

using namespace std;



std::atomic_bool flagStop;



void routine() {
    cout << "running..." << endl;

    while (1) {
        if (flagStop.load())
            break;

        std::this_thread::sleep_for(std::chrono::microseconds(500));
    }

    cout << "done" << endl;
}



int main() {
    flagStop.store(false);

    auto th = thread(routine);

    std::this_thread::sleep_for(std::chrono::seconds(3));

    flagStop.store(true);

    th.join();
    return 0;
}
