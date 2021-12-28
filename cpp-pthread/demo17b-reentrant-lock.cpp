/*
REENTRANT LOCK (RECURSIVE MUTEX)
Version B: Solving the problem from version A
*/


#include <iostream>
#include <pthread.h>
using namespace std;



pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;



void* routine(void*) {
    pthread_mutex_lock(&mut);
    cout << "First time acquiring the resource" << endl;

    pthread_mutex_lock(&mut);
    cout << "Second time acquiring the resource" << endl;

    pthread_mutex_unlock(&mut);
    pthread_mutex_unlock(&mut);

    pthread_exit(nullptr);
    return nullptr;
}



int main() {
    pthread_t tid;
    pthread_mutexattr_t attr;
    int ret = 0;

    ret = pthread_mutexattr_init(&attr);
    ret = pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
    ret = pthread_mutex_init(&mut, &attr);

    ret = pthread_create(&tid, nullptr, routine, nullptr);
    ret = pthread_join(tid, nullptr);

    ret = pthread_mutexattr_destroy(&attr);
    ret = pthread_mutex_destroy(&mut);

    return 0;
}
