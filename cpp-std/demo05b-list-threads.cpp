/*
DEMO LIST OF MUTIPLE THREADS
*/


#include <iostream>
#include <vector>
#include <thread>
using namespace std;



void routine(int index) {
    cout << index;
}



int main() {
    constexpr int NUM_THREADS = 5;
    vector<thread> lstTh;


    for (int i = 0; i < NUM_THREADS; ++i) {
        lstTh.push_back(thread(routine, i));

        // or...
        // auto th = thread(routine, i);
        // lstTh.push_back(std::move(th)); // because std::thread does not have copy constructors
    }


    for (auto &&th : lstTh) {
        th.join();
    }


    cout << endl;
    return 0;
}