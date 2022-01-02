/*
ATOMIC ACCESS
*/


#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <atomic>
using namespace std;



std::atomic_int32_t counter;



void doTask() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    counter += 1;
}



int main() {
    counter = 0;

    vector<std::thread> lstTh;

    for (int i = 0; i < 1000; ++i) {
        lstTh.push_back(std::thread(doTask));
    }

    for (auto&& th : lstTh) {
        th.join();
    }

    // counter = 1000
    cout << "counter = " << counter << endl;
    return 0;
}
