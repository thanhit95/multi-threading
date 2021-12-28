/*
BARRIER
Version A: Cyclic barrier
*/


#include <iostream>
#include <string>
#include <tuple>
#include <thread>
#include <barrier>
#include <chrono>
using namespace std;



auto syncPointA = std::barrier(2);
auto syncPointB = std::barrier(2);



void processRequest(string userName, int timeWait) {
    std::this_thread::sleep_for(std::chrono::seconds(timeWait));

    cout << "Get request from " << userName << endl;

    syncPointA.arrive_and_wait();

    cout << "Process request for " << userName << endl;

    syncPointB.arrive_and_wait();

    cout << "Done " << userName << endl;
}



int main() {
    constexpr int NUM_THREADS = 4;
    std::thread lstTh[NUM_THREADS];


    // tuple<userName, timeWait>
    tuple<string,int> arg[NUM_THREADS] = {
        { "foo", 1 },
        { "bar", 3 },
        { "ham", 3 },
        { "egg", 10 }
    };


    for (int i = 0; i < NUM_THREADS; ++i) {
        auto&& argItem = arg[i];
        lstTh[i] = std::thread(processRequest, std::get<0>(argItem), std::get<1>(argItem));
    }


    for (auto&& th : lstTh) {
        th.join();
    }


    return 0;
}
