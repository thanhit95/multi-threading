/*
DEMO LIST OF MUTIPLE THREADS
*/


#include <iostream>
#include <vector>
#include <pthread.h>
using namespace std;



void* routine(void* arg) {
    auto index = *(int*)arg;
    cout << index;

    pthread_exit(nullptr);
    return nullptr;
}



int main() {
    constexpr int NUM_THREADS = 5;

    vector<pthread_t> lstTid(NUM_THREADS);
    vector<int> arg(NUM_THREADS);

    int ret = 0;


    for (int i = 0; i < NUM_THREADS; ++i) {
        arg[i] = i;
        ret = pthread_create(&lstTid[i], nullptr, routine, &arg[i]);
    }


    for (auto&& tid : lstTid) {
        ret = pthread_join(tid, nullptr);
    }


    cout << endl;
    return 0;
}
