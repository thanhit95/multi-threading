/*
BARRIERS AND LATCHES
Version B: Count-down latches

Main thread waits for 3 child threads to get enough data to progress.

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



constexpr int NUM_THREADS = 3;
mylib::CountDownLatch syncPoint(NUM_THREADS);



void* doTask(void* argVoid) {
    auto arg = *(tuple<string,int>*) argVoid;
    string message = std::get<0>(arg);
    int waitTime = std::get<1>(arg);

    sleep(waitTime);

    cout << message << endl;
    syncPoint.countDown();

    sleep(8);
    cout << "Cleanup" << endl;

    pthread_exit(nullptr);
    return nullptr;
}



int main() {
    pthread_t lstTid[NUM_THREADS];
    int ret = 0;

    // tuple<message, waitTime>
    tuple<string,int> lstArg[NUM_THREADS] = {
        { "Send request to egg.net to get data", 6 },
        { "Send request to foo.org to get data", 2 },
        { "Send request to bar.com to get data", 4 }
    };

    for (int i = 0; i < NUM_THREADS; ++i) {
        ret = pthread_create(&lstTid[i], nullptr, &doTask, &lstArg[i]);
    }

    syncPoint.wait();
    cout << "\nNow we have enough data to progress to next step\n" << endl;

    for (auto&& tid : lstTid) {
        ret = pthread_join(tid, nullptr);
    }

    return 0;
}
