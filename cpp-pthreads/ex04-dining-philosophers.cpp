/*
THE DINING PHILOSOPHERS PROBLEM


PROBLEM STATEMENT
    The dining philosophers problem states that there are 5 philosophers sharing a circular table
    and they eat and think alternatively.
    There is a bowl of rice for each of the philosophers and 5 chopsticks.
    A philosopher needs both their right and left chopstick to eat.
    A hungry philosopher may only eat if there are both chopsticks available.
    Otherwise a philosopher puts down their chopstick and begin thinking again.


SOLUTION
    A solution of the dining philosophers problem is to use a semaphore to represent a chopstick.
    A chopstick can be picked up by executing a wait operation on the semaphore
    and released by executing a signal semaphore.

    The structure of a random philosopher i is given as follows:
    while true do
        wait( chopstick[i] );
        wait( chopstick[ (i+1) % 5] );

        EATING THE RICE

        signal( chopstick[i] );
        signal( chopstick[ (i+1) % 5] );

        THINKING

    What's the problem here?
    - Deadlock.
    - Starvation.

    The above solution makes sure that no two neighboring philosophers can eat at the same time.
    But this solution can lead to a deadlock.
    This may happen if all the philosophers pick their left chopstick simultaneously.
    Then none of them can eat and deadlock occurs.

    Some of the ways to avoid deadlock are as follows:
    - An even philosopher should pick the right chopstick and then the left chopstick
    while an odd philosopher should pick the left chopstick and then the right chopstick.
    - A philosopher should only be allowed to pick their chopstick if both are available at the same time.

*/


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


    // PREPARE ARGUMENTS
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        sem_init(&chopstick[i], 0, 1); // set semaphore = 1
        funcArg[i].chopstick = chopstick;
        funcArg[i].numPhilo = NUM_PHILOSOPHERS;
        funcArg[i].idPhiLo = i;
    }


    // CREATE THREADS
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        ret = pthread_create(&tid[i], nullptr, funcPhilosopher, (void*)&funcArg[i]);
    }


    // JOIN THREADS
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        ret = pthread_join(tid[i], nullptr);
    }


    // CLEAN UP
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        sem_destroy(&chopstick[i]);
    }

    return 0;
}
