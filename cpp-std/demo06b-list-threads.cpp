/*
LIST OF MUTIPLE THREADS
Version B: Using the std::vector
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

    vector<std::thread> lstTh;


    for (int i = 0; i < NUM_THREADS; ++i) {
        lstTh.push_back(std::thread(routine, i));

        // or...
        // auto th = std::thread(routine, i);
        // lstTh.push_back(std::move(th)); // because std::thread does not have copy constructors
    }


    for (auto&& th : lstTh) {
        th.join();
    }


    cout << endl;
    return 0;
}
