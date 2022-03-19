/*
REENTRANT LOCKS (RECURSIVE MUTEXES)
Version B: Solving the problem from version A
*/


#include <iostream>
#include <boost/thread.hpp>
using namespace std;



boost::recursive_mutex mut;



void doTask() {
    mut.lock();
    cout << "First time acquiring the resource" << endl;

    mut.lock();
    cout << "Second time acquiring the resource" << endl;

    mut.unlock();
    mut.unlock();
}



void doTaskUsingSyncBlock() {
    typedef boost::unique_lock<boost::recursive_mutex> uniquelk;

    uniquelk(mut);
    cout << "First time acquiring the resource" << endl;

    {
        uniquelk(mut);
        cout << "Second time acquiring the resource" << endl;
    }
}



int main() {
    boost::thread th(&doTask);
    th.join();
    return 0;
}
