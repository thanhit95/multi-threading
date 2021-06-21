/*
DEMO LIST OF MUTIPLE THREADS
*/


#include <iostream>
#include <thread>
using namespace std;



void routine(int index) {
    cout << index;
}



int main() {
    constexpr int NUM_THREADS = 5;

    std::thread lstTh[NUM_THREADS];


    for (int i = 0; i < NUM_THREADS; ++i) {
        lstTh[i] = std::thread(routine, i);
    }


    for (auto&& th : lstTh) {
        th.join();
    }


    cout << endl;
    return 0;
}
