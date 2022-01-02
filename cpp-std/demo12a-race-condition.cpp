/*
RACE CONDITIONS
*/


#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
using namespace std;



void doTask(int index) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    cout << index;
}



int main() {
    constexpr int NUM_THREADS = 4;
    vector<std::thread> lstTh;


    for (int i = 0; i < NUM_THREADS; ++i) {
        lstTh.push_back(
            std::thread(doTask, i)
        );
    }


    for (auto&& th : lstTh) {
        th.join();
    }


    cout << endl;
    return 0;
}
