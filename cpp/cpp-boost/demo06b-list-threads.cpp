/*
LIST OF MULTIPLE THREADS
Version B: Using the std::vector
*/


#include <iostream>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
using namespace std;



typedef boost::shared_ptr<boost::thread> threadptr;



void doTask(int index) {
    cout << index;
}



int main() {
    const int NUM_THREADS = 5;

    vector<threadptr> lstTh;

    for (int i = 0; i < NUM_THREADS; ++i) {
        threadptr ptr = boost::make_shared<boost::thread>(doTask, i);
        lstTh.push_back(ptr);
    }

    for (int i = 0; i < lstTh.size(); ++i) {
        lstTh[i]->join();
    }

    cout << endl;
    return 0;
}
