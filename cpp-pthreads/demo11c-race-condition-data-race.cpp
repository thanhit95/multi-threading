/*
RACE CONDITION AND DATA RACE
*/


#include <iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;



int counter = 0;



void* routineA(void*) {
    sleep(1);

    while (counter < 10)
        ++counter;

    cout << "A won !!!" << endl;

    pthread_exit(nullptr);
    return (void*)0;
}



void* routineB(void*) {
    sleep(1);

    while (counter > -10)
        --counter;

    cout << "B won !!!" << endl;

    pthread_exit(nullptr);
    return (void*)0;
}



int main() {
    pthread_t tidA, tidB;
    int ret = 0;

    ret = pthread_create(&tidA, nullptr, routineA, nullptr);
    ret = pthread_create(&tidB, nullptr, routineB, nullptr);

    ret = pthread_join(tidA, nullptr);
    ret = pthread_join(tidB, nullptr);

    return 0;
}
