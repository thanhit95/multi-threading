/*
REENTRANT LOCKS (RECURSIVE MUTEXES)
Version A: Introduction to reentrant locks
*/


#include <iostream>
#include <pthread.h>
using namespace std;



pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;



void* doTask(void*) {
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
    int ret = 0;

    ret = pthread_create(&tid, nullptr, &doTask, nullptr);

    /*
    The thread tid shall meet deadlock.
    So, you will never get output "Second time acquiring the resource".
    */

    ret = pthread_join(tid, nullptr);

    ret = pthread_mutex_destroy(&mut);

    return 0;
}
