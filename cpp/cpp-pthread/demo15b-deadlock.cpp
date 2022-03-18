/*
DEADLOCK
Version B
*/


#include <iostream>
#include <unistd.h>
#include <pthread.h>
using namespace std;



pthread_mutex_t mutResourceA = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutResourceB = PTHREAD_MUTEX_INITIALIZER;



void* foo(void*) {
    pthread_mutex_lock(&mutResourceA);
    cout << "foo acquired resource A" << endl;

    sleep(1);

    pthread_mutex_lock(&mutResourceB);
    cout << "foo acquired resource B" << endl;
    pthread_mutex_unlock(&mutResourceB);

    pthread_mutex_unlock(&mutResourceA);

    pthread_exit(nullptr);
    return nullptr;
}



void* bar(void*) {
    pthread_mutex_lock(&mutResourceB);
    cout << "bar acquired resource B" << endl;

    sleep(1);

    pthread_mutex_lock(&mutResourceA);
    cout << "bar acquired resource A" << endl;
    pthread_mutex_unlock(&mutResourceA);

    pthread_mutex_unlock(&mutResourceB);

    pthread_exit(nullptr);
    return nullptr;
}



int main() {
    pthread_t tidFoo, tidBar;
    int ret = 0;

    ret = pthread_create(&tidFoo, nullptr, &foo, nullptr);
    ret = pthread_create(&tidBar, nullptr, &bar, nullptr);

    ret = pthread_join(tidFoo, nullptr);
    ret = pthread_join(tidBar, nullptr);

    ret = pthread_mutex_destroy(&mutResourceA);
    ret = pthread_mutex_destroy(&mutResourceB);

    cout << "You will never see this statement due to deadlock!" << endl;
    return 0;
}
