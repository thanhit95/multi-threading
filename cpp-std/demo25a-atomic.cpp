/*
ATOMIC ACCESS
*/


#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
using namespace std;



volatile int counter = 0;



void routine() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    counter += 1;
}



int main() {
    counter = 0;

    vector<std::thread> lstTh;

    for (int i = 0; i < 1000; ++i) {
        lstTh.push_back(std::thread(routine));
    }

    for (auto&& th : lstTh) {
        th.join();
    }

    // Unpredictable result
    cout << "counter = " << counter << endl;
    return 0;
}
