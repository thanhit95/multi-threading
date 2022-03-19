/*
BARRIERS
Version B: Count-down latches

Main thread waits for 3 child threads to get enough data to progress.
*/


#include <iostream>
#include <string>
#include <tuple>
#include <chrono>
#include <thread>
#include <latch>
using namespace std;



constexpr int NUM_THREADS = 3;
auto syncPoint = std::latch(NUM_THREADS);



void doTask(string message, int timeWait) {
    std::this_thread::sleep_for(std::chrono::seconds(timeWait));

    cout << message << endl;
    syncPoint.count_down();

    std::this_thread::sleep_for(std::chrono::seconds(8));
    cout << "Cleanup" << endl;
}



int main() {
    std::thread lstTh[NUM_THREADS];

    // tuple<message, timeWait>
    tuple<string,int> lstArg[NUM_THREADS] = {
        { "Send request to egg.net to get data", 6 },
        { "Send request to foo.org to get data", 2 },
        { "Send request to bar.com to get data", 4 }
    };

    for (int i = 0; i < NUM_THREADS; ++i) {
        auto&& arg = lstArg[i];
        lstTh[i] = std::thread(&doTask, std::get<0>(arg), std::get<1>(arg));
    }

    syncPoint.wait();
    cout << "\nNow we has enough data to progress to next step\n" << endl;

    for (auto&& th : lstTh) {
        th.join();
    }

    return 0;
}
