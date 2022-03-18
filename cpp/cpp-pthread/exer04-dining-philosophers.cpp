/*
THE DINING PHILOSOPHERS PROBLEM
*/


#include <iostream>
#include <unistd.h>
#include <pthread.h>
using namespace std;



struct TaskArg {
    pthread_mutex_t* chopstick;
    int numPhilo;
    int idPhiLo;
};



void* doTaskPhilosopher(void *argVoid) {
    auto arg = (TaskArg*) argVoid;

    auto chopstick = arg->chopstick;
    int n = arg->numPhilo;
    int i = arg->idPhiLo;

    sleep(1);

    pthread_mutex_lock(&chopstick[i]);
    pthread_mutex_lock(&chopstick[(i + 1) % n]);

    cout << "Philosopher #" << i << " is eating the rice" << endl;

    pthread_mutex_unlock(&chopstick[i]);
    pthread_mutex_unlock(&chopstick[(i + 1) % n]);

    pthread_exit(nullptr);
    return nullptr;
}



int main() {
    constexpr int NUM_PHILOSOPHERS = 5;

    pthread_t tid[NUM_PHILOSOPHERS];
    pthread_mutex_t chopstick[NUM_PHILOSOPHERS];
    TaskArg arg[NUM_PHILOSOPHERS];

    int ret = 0;


    // PREPARE ARGUMENTS
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        chopstick[i] = PTHREAD_MUTEX_INITIALIZER;
        arg[i].chopstick = chopstick;
        arg[i].numPhilo = NUM_PHILOSOPHERS;
        arg[i].idPhiLo = i;
    }


    // CREATE THREADS
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        ret = pthread_create(&tid[i], nullptr, &doTaskPhilosopher, &arg[i]);
    }


    // JOIN THREADS
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        ret = pthread_join(tid[i], nullptr);
    }


    // CLEAN UP
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        ret = pthread_mutex_destroy(&chopstick[i]);
    }

    return 0;
}
