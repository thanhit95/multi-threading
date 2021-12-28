/*
SEMAPHORES
Version B: Tires and chassis
*/


#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
using namespace std;



sem_t semTire;
sem_t semChassis;



void* makeTire(void*) {
    int ret = 0;

    for (int i = 0; i < 8; ++i) {
        sem_wait(&semTire);

        cout << "Make 1 tire" << endl;
        sleep(1);

        sem_post(&semChassis);
    }

    pthread_exit(nullptr);
    return nullptr;
}



void* makeChassis(void*) {
    for (int i = 0; i < 4; ++i) {
        sem_wait(&semChassis);
        sem_wait(&semChassis);
        sem_wait(&semChassis);
        sem_wait(&semChassis);

        cout << "Make 1 chassis" << endl;
        sleep(3);

        sem_post(&semTire);
        sem_post(&semTire);
        sem_post(&semTire);
        sem_post(&semTire);
    }

    pthread_exit(nullptr);
    return nullptr;
}



int main() {
    pthread_t tidTireA, tidTireB, tidChassis;
    int ret = 0;

    ret = sem_init(&semTire, 0, 4);
    ret = sem_init(&semChassis, 0, 0);

    ret = pthread_create(&tidTireA, nullptr, makeTire, nullptr);
    ret = pthread_create(&tidTireB, nullptr, makeTire, nullptr);
    ret = pthread_create(&tidChassis, nullptr, makeChassis, nullptr);

    ret = pthread_join(tidTireA, nullptr);
    ret = pthread_join(tidTireB, nullptr);
    ret = pthread_join(tidChassis, nullptr);

    ret = sem_destroy(&semTire);
    ret = sem_destroy(&semChassis);

    return 0;
}
