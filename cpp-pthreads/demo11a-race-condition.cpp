/*
RACE CONDITION

A race condition or race hazard is the condition of an electronics, software, or other system
where the system's substantive behavior is dependent on the sequence or timing of other uncontrollable events.

This program illustrates race condition:
    Each time you run the program, the display results are different.
*/


#include <iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;



void* routine(void *arg) {
    int index = *(int*)arg;

    sleep(1);

    cout << index;

    pthread_exit(nullptr);
    return (void*)0;
}



int main() {
    constexpr int NUM_THREADS = 4;
    pthread_t tid[NUM_THREADS];
    int arg[NUM_THREADS];

    int ret = 0;


    for (int i = 0; i < NUM_THREADS; ++i) {
        arg[i] = i;
        ret = pthread_create(&tid[i], nullptr, routine, (void*)&arg[i]);
    }


    for (int i = 0; i < NUM_THREADS; ++i) {
        ret = pthread_join(tid[i], nullptr);
    }


    cout << endl;
    return 0;
}
