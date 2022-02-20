/*
LIST OF MULTIPLE THREADS
Version B: Using the std::vector
*/


#include <iostream>
#include <vector>
#include <pthread.h>
using namespace std;



void* doTask(void* arg) {
    auto index = *(int*) arg;
    cout << index;

    pthread_exit(nullptr);
    return nullptr;
}



int main() {
    constexpr int NUM_THREADS = 5;

    vector<pthread_t> lstTid(NUM_THREADS);
    vector<int> lstArg(NUM_THREADS);

    int ret = 0;


    for (int i = 0; i < NUM_THREADS; ++i) {
        lstArg[i] = i;
        ret = pthread_create(&lstTid[i], nullptr, doTask, &lstArg[i]);
    }

    for (auto&& tid : lstTid) {
        ret = pthread_join(tid, nullptr);
    }


    cout << endl;
    return 0;
}
