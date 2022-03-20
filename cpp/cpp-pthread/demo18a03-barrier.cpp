/*
BARRIERS AND LATCHES
Version A: Cyclic barriers
*/


#include <iostream>
#include <string>
#include <tuple>
#include <unistd.h>
#include <pthread.h>
using namespace std;



pthread_barrier_t syncPointA;
pthread_barrier_t syncPointB;



void* processRequest(void* argVoid) {
    auto arg = *(tuple<string,int>*) argVoid;
    string userName = std::get<0>(arg);
    int waitTime = std::get<1>(arg);

    sleep(waitTime);

    cout << "Get request from " << userName << endl;
    pthread_barrier_wait(&syncPointA);

    cout << "Process request for " << userName << endl;
    pthread_barrier_wait(&syncPointB);

    cout << "Done " << userName << endl;

    pthread_exit(nullptr);
    return nullptr;
}



int main() {
    constexpr int NUM_THREADS = 4;
    pthread_t lstTid[NUM_THREADS];
    int ret = 0;

    // tuple<userName, waitTime>
    tuple<string,int> lstArg[NUM_THREADS] = {
        { "lorem", 1 },
        { "ipsum", 3 },
        { "dolor", 3 },
        { "amet", 10 }
    };

    ret = pthread_barrier_init(&syncPointA, nullptr, 2);
    ret = pthread_barrier_init(&syncPointB, nullptr, 2);

    for (int i = 0; i < NUM_THREADS; ++i) {
        ret = pthread_create(&lstTid[i], nullptr, &processRequest, &lstArg[i]);
    }

    for (auto&& tid : lstTid) {
        ret = pthread_join(tid, nullptr);
    }

    ret = pthread_barrier_destroy(&syncPointA);
    ret = pthread_barrier_destroy(&syncPointB);
    return 0;
}
