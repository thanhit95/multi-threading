/*
REENTRANT LOCKS (RECURSIVE MUTEXES)
Version A: Introduction to reentrant locks
*/


#include <iostream>
#include <thread>
#include <mutex>
using namespace std;



std::mutex mut;



void routine() {
    mut.lock();
    cout << "First time acquiring the resource" << endl;

    mut.lock();
    cout << "Second time acquiring the resource" << endl;

    mut.unlock();
    mut.unlock();
}



int main() {
    auto th = std::thread(routine);

    /*
    The function "routine" will meet deadlock.
    So, you will never get output "Second time acquiring the resource".
    */

    th.join();

    return 0;
}
