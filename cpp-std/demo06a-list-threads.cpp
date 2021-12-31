/*
LIST OF MUTIPLE THREADS
Version A: Using standard arrays
*/


#include <iostream>
#include <thread>
using namespace std;



void doTask(int index) {
    cout << index;
}



int main() {
    constexpr int NUM_THREADS = 5;

    std::thread lstTh[NUM_THREADS];


    for (int i = 0; i < NUM_THREADS; ++i) {
        lstTh[i] = std::thread(doTask, i);
    }


    for (auto&& th : lstTh) {
        th.join();
    }


    cout << endl;
    return 0;
}
