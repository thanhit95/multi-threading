/*
RACE CONDITIONS
*/


#include <iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;



void* routine(void* arg) {
    int index = *(int*)arg;

    sleep(1);

    cout << index;

    pthread_exit(nullptr);
    return nullptr;
}



int main() {
    constexpr int NUM_THREADS = 4;

    pthread_t lstTid[NUM_THREADS];
    int arg[NUM_THREADS];

    int ret = 0;


    for (int i = 0; i < NUM_THREADS; ++i) {
        arg[i] = i;
        ret = pthread_create(&lstTid[i], nullptr, routine, &arg[i]);
    }


    for (int i = 0; i < NUM_THREADS; ++i) {
        ret = pthread_join(lstTid[i], nullptr);
    }


    cout << endl;
    return 0;
}
