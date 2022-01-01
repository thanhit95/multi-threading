/*
DEADLOCK
Version A
*/


#include <iostream>
#include <pthread.h>
using namespace std;



pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;



void* doTask(void* arg) {
    auto name = (const char*) arg;

    pthread_mutex_lock(&mut);

    cout << name << " acquired resource" << endl;

    // pthread_mutex_unlock(&mut); // forget this statement ==> deadlock

    pthread_exit(nullptr);
    return nullptr;
}



int main() {
    pthread_t tidFoo, tidBar;
    int ret = 0;

    ret = pthread_create(&tidFoo, nullptr, doTask, (void*)"foo");
    ret = pthread_create(&tidBar, nullptr, doTask, (void*)"bar");

    ret = pthread_join(tidFoo, nullptr);
    ret = pthread_join(tidBar, nullptr);

    cout << "You will never see this statement due to deadlock!" << endl;
    return 0;
}
