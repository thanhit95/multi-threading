/*
RACE CONDITION AND DATA RACE
*/


#include <iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;



int counter = 0;



void* foo(void*) {
    sleep(1);
    counter += 1;

    pthread_exit(nullptr);
    return (void*)0;
}



void* bar(void*) {
    sleep(1);
    counter += 2;

    pthread_exit(nullptr);
    return (void*)0;
}



int main() {
    pthread_t tidFoo, tidBar;
    int ret = 0;

    ret = pthread_create(&tidFoo, nullptr, foo, nullptr);
    ret = pthread_create(&tidBar, nullptr, bar, nullptr);

    ret = pthread_join(tidFoo, nullptr);
    ret = pthread_join(tidBar, nullptr);

    cout << "counter = " << counter << endl;
    /*
    counter can be 1, 2 or 3
    */

    return 0;
}
