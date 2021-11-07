/*
MUTEX (Mutual Exclusion)

Without synchronization (by a mutex), we are not sure that result = 30000
*/


#include <iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;



pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
int counter = 0;



void* routineCounter(void*) {
    sleep(1);

    pthread_mutex_lock(&mut);

    for (int i = 0; i < 10000; ++i)
        ++counter;

    pthread_mutex_unlock(&mut);

    pthread_exit(nullptr);
    return nullptr;
}



int main() {
    constexpr int NUM_THREADS = 3;
    pthread_t lstTid[NUM_THREADS];
    int ret = 0;


    counter = 0;


    for (auto&& tid : lstTid) {
        ret = pthread_create(&tid, nullptr, routineCounter, nullptr);
    }


    for (auto&& tid : lstTid) {
        ret = pthread_join(tid, nullptr);
    }


    ret = pthread_mutex_destroy(&mut);


    cout << "counter = " << counter << endl;
    return 0;
}
