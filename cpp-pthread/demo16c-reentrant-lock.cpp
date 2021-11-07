/*
REENTRANT LOCK (RECURSIVE MUTEX)
Version C: Slightly hard example
*/


#include <iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;



pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;



void* routine(void* arg) {
    char name = *(char*)arg;
    sleep(1);

    pthread_mutex_lock(&mut);
    cout << "First time " << name << " acquiring the resource" << endl;

    pthread_mutex_lock(&mut);
    cout << "Second time " << name << " acquiring the resource" << endl;

    pthread_mutex_unlock(&mut);
    pthread_mutex_unlock(&mut);

    pthread_exit(nullptr);
    return nullptr;
}



int main() {
    constexpr int NUM_THREADS = 3;


    pthread_t lstTid[NUM_THREADS];
    char arg[NUM_THREADS];

    pthread_mutexattr_t attr;
    int ret = 0;


    ret = pthread_mutexattr_init(&attr);
    ret = pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
    ret = pthread_mutex_init(&mut, &attr);


    for (int i = 0; i < NUM_THREADS; ++i) {
        arg[i] = char(i + 'A');
        ret = pthread_create(&lstTid[i], nullptr, routine, &arg[i]);
    }


    for (auto&& tid : lstTid) {
        ret = pthread_join(tid, nullptr);
    }


    pthread_mutexattr_destroy(&attr);
    pthread_mutex_destroy(&mut);


    return 0;
}
