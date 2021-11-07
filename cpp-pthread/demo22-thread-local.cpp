/*
THREAD-LOCAL STORAGE
The code is specific for gcc.
*/


#include <iostream>
#include <vector>
#include <pthread.h>
#include <unistd.h>
using namespace std;



__thread int counter = 0;



void* routine(void* arg) {
    auto t = *(int*)arg;

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
    int arg[NUM_THREADS];

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
