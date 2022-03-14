/*
BARRIERS
Version A: Cyclic barriers
*/


#include <iostream>
#include <string>
#include <tuple>
#include <unistd.h>
#include <pthread.h>
using namespace std;



pthread_barrier_t syncPoint;



void* processRequest(void* argVoid) {
    auto arg = *(tuple<string,int>*) argVoid;
    string userName = std::get<0>(arg);
    int timeWait = std::get<1>(arg);

    sleep(timeWait);

    cout << "Get request from " << userName << endl;

    pthread_barrier_wait(&syncPoint);

    cout << "Process request for " << userName << endl;

    pthread_barrier_wait(&syncPoint);

    cout << "Done " << userName << endl;

    pthread_exit(nullptr);
    return nullptr;
}



int main() {
    constexpr int NUM_THREADS = 3;
    pthread_t lstTid[NUM_THREADS];
    int ret = 0;

    // tuple<userName, timeWait>
    tuple<string,int> lstArg[NUM_THREADS] = {
        { "lorem", 1 },
        { "ipsum", 2 },
        { "dolor", 3 },
    };

    ret = pthread_barrier_init(&syncPoint, nullptr, 3); // participant count = 3

    for (int i = 0; i < NUM_THREADS; ++i) {
        ret = pthread_create(&lstTid[i], nullptr, processRequest, &lstArg[i]);
    }

    for (auto&& tid : lstTid) {
        ret = pthread_join(tid, nullptr);
    }

    ret = pthread_barrier_destroy(&syncPoint);
    return 0;
}
