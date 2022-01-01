/*
RACE CONDITIONS AND DATA RACES
*/


#include <iostream>
#include <unistd.h>
#include <pthread.h>
using namespace std;



int counter = 0;



void* increaseCounter(void*) {
    for (int i = 0; i < 500; ++i) {
        usleep(3);
        counter += 1;
    }

    pthread_exit(nullptr);
    return nullptr;
}



int main() {
    pthread_t tidFoo, tidBar, tidEgg;
    int ret = 0;

    ret = pthread_create(&tidFoo, nullptr, increaseCounter, nullptr);
    ret = pthread_create(&tidBar, nullptr, increaseCounter, nullptr);
    ret = pthread_create(&tidEgg, nullptr, increaseCounter, nullptr);

    ret = pthread_join(tidFoo, nullptr);
    ret = pthread_join(tidBar, nullptr);
    ret = pthread_join(tidEgg, nullptr);

    cout << "counter = " << counter << endl;
    // We are not sure that counter = 1500

    return 0;
}
