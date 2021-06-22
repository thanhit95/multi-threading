/*
BARRIER

In cases where you must wait for a number of tasks to be completed before
an overall task can proceed, barrier synchronization can be used.
*/


#include <iostream>
#include <tuple>
#include <pthread.h>
#include <unistd.h>
#include "mytool-random.hpp"

using namespace std;



pthread_barrier_t barrier;



void* packageProduct(void *argVoid) {
    auto arg = *(tuple<int,int> *)argVoid;
    int itemId = get<0>(arg);
    int timeWait = get<1>(arg);

    sleep(timeWait);

    cout << "Getting item " << itemId << endl;

    pthread_barrier_wait(&barrier);

    cout << "Packaging product" << endl;

    pthread_barrier_wait(&barrier);

    pthread_exit(nullptr);
    return (void*)0;
}



int main() {
    constexpr int NUM_THREADS = 6;
    pthread_t tid[NUM_THREADS];
    tuple<int,int> arg[NUM_THREADS];    // tuple<item id, waiting time>

    mytool::RandIntGenerator intGen(1, (int)(NUM_THREADS * 1.5));
    int ret = 0;


    ret = pthread_barrier_init(&barrier, nullptr, 3); // participant count = 3


    for (int i = 0; i < NUM_THREADS; ++i) {
        arg[i] = make_tuple(i, intGen.get());
        ret = pthread_create(&tid[i], nullptr, packageProduct, (void*)&arg[i]);
    }


    for (int i = 0; i < NUM_THREADS; ++i) {
        ret = pthread_join(tid[i], nullptr);
    }


    ret = pthread_barrier_destroy(&barrier);
    return 0;
}
