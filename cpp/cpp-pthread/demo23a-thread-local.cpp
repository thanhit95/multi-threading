/*
THREAD-LOCAL STORAGE
Introduction

The code is specific for gcc.
*/


#include <iostream>
#include <pthread.h>
using namespace std;



__thread int value = 123;



void* doTask(void* arg) {
    cout << value << endl;
    pthread_exit(nullptr);
    return nullptr;
}



int main() {
    pthread_t tid;
    int ret = 0;

    // Main thread sets value = 999
    value = 999;
    cout << value << endl;

    // Child thread gets value
    // Expected output: 123
    ret = pthread_create(&tid, nullptr, &doTask, nullptr);
    ret = pthread_join(tid, nullptr);

    return 0;
}
