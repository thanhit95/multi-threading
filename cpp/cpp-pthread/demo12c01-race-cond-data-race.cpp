/*
RACE CONDITIONS AND DATA RACES
*/


#include <iostream>
#include <unistd.h>
#include <pthread.h>
using namespace std;



int counter = 0;



void* increaseCounter(void*) {
    sleep(1);

    for (int i = 0; i < 1000; ++i) {
        counter += 1;
    }

    pthread_exit(nullptr);
    return nullptr;
}



int main() {
    constexpr int NUM_THREADS = 16;
    pthread_t lstTid[NUM_THREADS];
    int ret = 0;

    for (int i = 0; i < NUM_THREADS; ++i) {
        ret = pthread_create(&lstTid[i], nullptr, &increaseCounter, nullptr);
    }

    for (int i = 0; i < NUM_THREADS; ++i) {
        ret = pthread_join(lstTid[i], nullptr);
    }

    cout << "counter = " << counter << endl;
    // We are NOT sure that counter = 16000

    return 0;
}
