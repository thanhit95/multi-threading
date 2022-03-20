/*
BARRIERS AND LATCHES
Version B: Count-down latches

Count-down latches in C++ POSIX threading are not supported by default.
So, I use mylib::CountDownLatch for this demonstration.
*/


#include <iostream>
#include <string>
#include <tuple>
#include <unistd.h>
#include <pthread.h>
#include "mylib-latch.hpp"
using namespace std;



mylib::CountDownLatch syncPoint(3);



void* processRequest(void* argVoid) {
    auto arg = *(tuple<string,int>*) argVoid;
    string userName = std::get<0>(arg);
    int waitTime = std::get<1>(arg);

    sleep(waitTime);

    cout << "Get request from " << userName << endl;

    syncPoint.countDown();
    syncPoint.wait();

    cout << "Done " << userName << endl;

    pthread_exit(nullptr);
    return nullptr;
}



int main() {
    constexpr int NUM_THREADS = 3;
    pthread_t lstTid[NUM_THREADS];
    int ret = 0;

    // tuple<userName, waitTime>
    tuple<string,int> lstArg[NUM_THREADS] = {
        { "lorem", 1 },
        { "ipsum", 2 },
        { "dolor", 3 }
    };

    for (int i = 0; i < NUM_THREADS; ++i) {
        ret = pthread_create(&lstTid[i], nullptr, &processRequest, &lstArg[i]);
    }

    for (auto&& tid : lstTid) {
        ret = pthread_join(tid, nullptr);
    }

    return 0;
}
