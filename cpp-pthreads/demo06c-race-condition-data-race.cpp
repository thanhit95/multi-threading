/*
RACE CONDITION AND DATA RACE

Ususally, race condition happens together with data race.
For an example: Two or more threads can access shared data and they try to change it at the same time.

Concurrent accesses to shared resources can lead to unexpected or erroneous behavior,
so parts of the program where the shared resource is accessed need to be protected in ways that
avoid the concurrent access. This protected section is the critical section or critical region.
*/


#include <iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;



int counter = 0;



void* routineA(void *) {
    sleep(1);

    while (counter < 10)
        ++counter;

    cout << "A won !!!" << endl;

    pthread_exit(nullptr);
    return (void*)0;
}



void* routineB(void *) {
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
