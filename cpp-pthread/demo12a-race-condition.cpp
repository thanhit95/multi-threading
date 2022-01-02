/*
RACE CONDITIONS
*/


#include <iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;



void* doTask(void* arg) {
    int index = *(int*) arg;

    sleep(1);

    cout << index;

    pthread_exit(nullptr);
    return nullptr;
}



int main() {
    constexpr int NUM_THREADS = 4;

    pthread_t lstTid[NUM_THREADS];
    int lstArg[NUM_THREADS];

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
