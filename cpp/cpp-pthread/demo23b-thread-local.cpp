/*
THREAD-LOCAL STORAGE
Avoiding synchronization using thread-local storage

The code is specific for gcc.
*/


#include <iostream>
#include <vector>
#include <unistd.h>
#include <pthread.h>
using namespace std;



__thread int counter = 0;



void* doTask(void* arg) {
    auto t = *(int*) arg;

    sleep(1);

    for (int i = 0; i < 1000; ++i)
        ++counter;

    cout << "Thread " << t << " gives counter = " << counter << endl;

    pthread_exit(nullptr);
    return nullptr;
}



int main() {
    constexpr int NUM_THREADS = 3;

    pthread_t lstTid[NUM_THREADS];
    int lstArg[NUM_THREADS];

    int ret = 0;

    for (int i = 0; i < NUM_THREADS; ++i) {
        lstArg[i] = i;
        ret = pthread_create(&lstTid[i], nullptr, &doTask, &lstArg[i]);
    }

    for (auto&& tid : lstTid) {
        ret = pthread_join(tid, nullptr);
    }

    cout << endl;
    return 0;
}
