/*
SEMAPHORE

A car is manufactured at each stop on a conveyor belt in a car factory.
A car is constructed from thefollowing parts: chassis, tires.
Thus there are 2 tasks in manufacturing a car.

However, 4 tires cannot be added until the chassis is placed on the belt.

There are:
- 2 production lines (i.e. 2 threads) of making tires.
- 1 production line (i.e. 1 thread) of making chassis.

Write a program to illustrate this scene.
*/


#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

using namespace std;



sem_t semTire;
sem_t semChassis;



void* makeTire(void *) {
    int ret = 0;

    for (int i = 0; i < 8; ++i) {
        sem_wait(&semChassis);

        cout << "make 1 tire" << endl;
        sleep(1);

        sem_post(&semTire);
    }

    pthread_exit(nullptr);
    return (void*)0;
}



void* makeChasis(void *) {
    for (int i = 0; i < 4; ++i) {
        sem_wait(&semTire);
        sem_wait(&semTire);
        sem_wait(&semTire);
        sem_wait(&semTire);

        cout << "make 1 chasis" << endl;
        sleep(3);

        sem_post(&semChassis);
        sem_post(&semChassis);
        sem_post(&semChassis);
        sem_post(&semChassis);
    }

    pthread_exit(nullptr);
    return (void*)0;
}



int main() {
    pthread_t tidTireA, tidTireB, tidChassis;
    int ret = 0;

    ret = sem_init(&semTire, 0, 0);
    ret = sem_init(&semChassis, 0, 4);

    ret = pthread_create(&tidTireA, nullptr, makeTire, nullptr);
    ret = pthread_create(&tidTireB, nullptr, makeTire, nullptr);
    ret = pthread_create(&tidChassis, nullptr, makeChasis, nullptr);

    ret = pthread_join(tidTireA, nullptr);
    ret = pthread_join(tidTireB, nullptr);
    ret = pthread_join(tidChassis, nullptr);

    ret = sem_destroy(&semTire);
    ret = sem_destroy(&semChassis);

    return 0;
}
