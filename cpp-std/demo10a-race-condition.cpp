#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
using namespace std;



void routine(int index) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    cout << index;
}



int main() {
    constexpr int NUM_THREADS = 4;
    vector<thread> lstTh;


    for (int i = 0; i < NUM_THREADS; ++i) {
        lstTh.push_back(
            thread(routine, i)
        );
    }


    for (auto &&th : lstTh) {
        th.join();
    }


    cout << endl;
    return 0;
}
