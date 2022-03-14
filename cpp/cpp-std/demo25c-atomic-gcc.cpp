/*
ATOMIC ACCESS
gcc builtins for atomic access

Some functions:
    type __atomic_load_n (type *ptr, int memorder)
    void __atomic_store (type *ptr, type *val, int memorder)

    type __atomic_add_fetch (type *ptr, type val, int memorder)
    type __atomic_sub_fetch (type *ptr, type val, int memorder)
    type __atomic_fetch_add (type *ptr, type val, int memorder)
    type __atomic_fetch_sub (type *ptr, type val, int memorder)
*/


#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
using namespace std;



volatile int counter = 0;



void doTask() {
    std::this_thread::sleep_for(std::chrono::seconds(1));

    __atomic_add_fetch(&counter, 1, __ATOMIC_SEQ_CST);

    //__sync_add_and_fetch(&counter, 1); // Before C++11
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
