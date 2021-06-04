#include <iostream>
#include <pthread.h>
#include <semaphore.h>

using namespace std;



struct FuncArg {
    sem_t *chopstick;
    int numPhilo;
    int idPhiLo;
};



void* funcPhilosopher(void *argVoid) {
    auto arg = (FuncArg*)argVoid;

    auto chopstick = arg->chopstick;
    int n = arg->numPhilo;
    int i = arg->idPhiLo;

    sem_wait(&chopstick[i]);
    sem_wait(&chopstick[(i + 1) % n]);

    cout << "philosopher #" << i << " is eating the rice" << endl;

    sem_post(&chopstick[i]);
    sem_post(&chopstick[(i + 1) % n]);

    pthread_exit(nullptr);
    return (void*)0;
}



int main() {
    constexpr int NUM_PHILOSOPHERS = 5;

    pthread_t tid[NUM_PHILOSOPHERS];
    sem_t chopstick[NUM_PHILOSOPHERS];
    FuncArg funcArg[NUM_PHILOSOPHERS];

    int ret = 0;


    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        sem_init(&chopstick[i], 0, 1); // set semaphore = 1
        funcArg[i].chopstick = chopstick;
        funcArg[i].numPhilo = NUM_PHILOSOPHERS;
        funcArg[i].idPhiLo = i;
    }


    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        ret = pthread_create(&tid[i], nullptr, funcPhilosopher, (void*)&funcArg[i]);
    }


    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        ret = pthread_join(tid[i], nullptr);
    }

    return 0;
}
