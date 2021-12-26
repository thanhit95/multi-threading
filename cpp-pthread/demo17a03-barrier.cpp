/*
BARRIER
Version A: Cyclic barrier
*/


#include <iostream>
#include <string>
#include <tuple>
#include <pthread.h>
#include <unistd.h>
using namespace std;



pthread_barrier_t syncPointA;
pthread_barrier_t syncPointB;



void* processRequest(void* argVoid) {
    auto arg = *(tuple<string,int>*)argVoid;
    string userName = get<0>(arg);
    int timeWait = get<1>(arg);

    sleep(timeWait);

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

    // tuple<userName, timeWait>
    tuple<string,int> arg[NUM_THREADS] = {
        { "foo", 1 },
        { "bar", 3 },
        { "ham", 3 },
        { "egg", 10 }
    };

    int ret = 0;


    ret = pthread_barrier_init(&syncPointA, nullptr, 2);
    ret = pthread_barrier_init(&syncPointB, nullptr, 2);


    for (int i = 0; i < NUM_THREADS; ++i) {
        auto&& argItem = arg[i];
        ret = pthread_create(&lstTid[i], nullptr, processRequest, &argItem);
    }


    for (auto&& tid : lstTid) {
        ret = pthread_join(tid, nullptr);
    }


    ret = pthread_barrier_destroy(&syncPointA);
    ret = pthread_barrier_destroy(&syncPointB);


    return 0;
}
