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

using namespace std;



pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
int count = 0;



void* funcCounter(void *) {
    pthread_mutex_lock(&mut);
    ++count;
    pthread_mutex_unlock(&mut);

    pthread_exit(nullptr);
    return (void*)0;
}



int main() {
    pthread_t tid1, tid2;
    int ret;


    count = 0;


    ret = pthread_create(&tid1, nullptr, funcCounter, nullptr);
    ret = pthread_create(&tid2, nullptr, funcCounter, nullptr);


    ret = pthread_join(tid1, nullptr);
    ret = pthread_join(tid2, nullptr);


    ret = pthread_mutex_destroy(&mut);


    cout << "count = " << count << endl;
    return 0;
}
