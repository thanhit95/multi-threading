/*
BARRIERS
Version B: Count-down latches
*/


#include <iostream>
#include <string>
#include <tuple>
#include <chrono>
#include <thread>
#include <latch>
using namespace std;



auto syncPoint = std::latch(3); // participant count = 3



void processRequest(string userName, int timeWait) {
    std::this_thread::sleep_for(std::chrono::seconds(timeWait));

    cout << "Get request from " << userName << endl;

    syncPoint.arrive_and_wait();

    cout << "Done " << userName << endl;
}



int main() {
    constexpr int NUM_THREADS = 3;
    std::thread lstTh[NUM_THREADS];

    // tuple<userName, timeWait>
    tuple<string,int> lstArg[NUM_THREADS] = {
        { "lorem", 1 },
        { "ipsum", 2 },
        { "dolor", 3 }
    };

    for (int i = 0; i < NUM_THREADS; ++i) {
        auto&& arg = lstArg[i];
        lstTh[i] = std::thread(&processRequest, std::get<0>(arg), std::get<1>(arg));
    }

    for (auto&& th : lstTh) {
        th.join();
    }

    return 0;
}
