/*
REENTRANT LOCKS (RECURSIVE MUTEXES)
Version B: Solving the problem from version A
*/


#include <iostream>
#include <thread>
#include <mutex>
using namespace std;



std::recursive_mutex mut;



void doTask() {
    mut.lock();
    cout << "First time acquiring the resource" << endl;

    mut.lock();
    cout << "Second time acquiring the resource" << endl;

    mut.unlock();
    mut.unlock();
}



void doTaskUsingSyncBlock() {
    using uniquelk = std::unique_lock<std::recursive_mutex>;

    uniquelk lk(mut);
    cout << "First time acquiring the resource" << endl;

    {
        uniquelk lk(mut);
        cout << "Second time acquiring the resource" << endl;
    }
}



int main() {
    auto th = std::thread(&doTask);
    th.join();
    return 0;
}
