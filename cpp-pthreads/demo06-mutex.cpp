/*
Mutexes are used to prevent data inconsistencies due to race conditions.
A race condition often occurs when two or more threads need to perform operations on the same memory area
but the results of computations depends on the order in which these operations are performed.

Mutexes are used for serializing shared resources.
Anytime a global resource is accessed by more than one thread the resource should have a Mutex associated with it.

One can apply a mutex to protect a segment of memory ("critical region") from other threads.
Mutexes can be applied only to threads in a single process and do not work between processes as do semaphores.
*/


#include <iostream>
#include <pthread.h>
#include <unistd.h>

using namespace std;



pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
int count = 0;



void* funcCounter(void *) {
    sleep(1);

    pthread_mutex_lock(&mut);

    for (int i = 0; i < 1000; ++i)
        ++count;

    pthread_mutex_unlock(&mut);

    pthread_exit(nullptr);
    return (void*)0;
}



int main() {
    constexpr int NUM_THREADS = 3;
    pthread_t tid[NUM_THREADS];
    int ret = 0;


    count = 0;


    for (auto &tidItem : tid) {
        ret = pthread_create(&tidItem, nullptr, funcCounter, nullptr);
    }


    for (auto &tidItem : tid) {
        ret = pthread_join(tidItem, nullptr);
    }


    ret = pthread_mutex_destroy(&mut);


    cout << "count = " << count << endl;
    return 0;
}
