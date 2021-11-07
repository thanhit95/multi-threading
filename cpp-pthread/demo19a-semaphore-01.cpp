/*
SEMAPHORE
Version A: Paper and packages
*/


#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
using namespace std;



sem_t semPackage;



void* makeOnePaper(void*) {
    for (int i = 0; i < 4; ++i) {
        cout << "Make 1 paper" << endl;
        sleep(1);

        sem_post(&semPackage);
    }

    pthread_exit(nullptr);
    return nullptr;
}



void* combineOnePackage(void*) {
    for (int i = 0; i < 4; ++i) {
        sem_wait(&semPackage);
        sem_wait(&semPackage);
        cout << "Combine 2 papers into 1 package" << endl;
    }

    pthread_exit(nullptr);
    return nullptr;
}



int main() {
    pthread_t tidMakePaperA, tidMakePaperB, tidCombinePackage;
    int ret = 0;

    ret = sem_init(&semPackage, 0, 0);

    ret = pthread_create(&tidMakePaperA, nullptr, makeOnePaper, nullptr);
    ret = pthread_create(&tidMakePaperB, nullptr, makeOnePaper, nullptr);
    ret = pthread_create(&tidCombinePackage, nullptr, combineOnePackage, nullptr);

    ret = pthread_join(tidMakePaperA, nullptr);
    ret = pthread_join(tidMakePaperB, nullptr);
    ret = pthread_join(tidCombinePackage, nullptr);

    ret = sem_destroy(&semPackage);
    return 0;
}
