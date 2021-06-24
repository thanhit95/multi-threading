#include <iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;



pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t conditionVar = PTHREAD_COND_INITIALIZER;



void* foo(void*) {
    cout << "foo is waiting..." << endl;

    pthread_mutex_lock(&mut);
    pthread_cond_wait(&conditionVar, &mut);

    cout << "foo resumed" << endl;

    pthread_mutex_unlock(&mut);

    pthread_exit(nullptr);
    return nullptr;
}



void* bar(void*) {
    sleep(3);
    pthread_cond_broadcast(&conditionVar);

    pthread_exit(nullptr);
    return nullptr;
}



int main() {
    constexpr int NUM_TH_FOO = 3;

    pthread_t lstTidFoo[NUM_TH_FOO];
    pthread_t tidBar;

    int ret = 0;


    for (auto&& tid : lstTidFoo) {
        ret = pthread_create(&tid, nullptr, foo, nullptr);
    }

    ret = pthread_create(&tidBar, nullptr, bar, nullptr);


    for (auto&& tid : lstTidFoo) {
        ret = pthread_join(tid, nullptr);
    }

    ret = pthread_join(tidBar, nullptr);


    ret = pthread_cond_destroy(&conditionVar);
    ret = pthread_mutex_destroy(&mut);

    return 0;
}
