/*
SEMAPHORE
Version A: Paper sheets and packages
*/


#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
using namespace std;



sem_t semPackage;
sem_t semPaper;



void* makeOnePaper(void*) {
    for (int i = 0; i < 4; ++i) {
        sem_wait(&semPaper);

        cout << "Make 1 sheet" << endl;

        sem_post(&semPackage);
    }

    pthread_exit(nullptr);
    return nullptr;
}



void* combineOnePackage(void*) {
    for (int i = 0; i < 4; ++i) {
        sem_wait(&semPackage);
        sem_wait(&semPackage);

        cout << "Combine 2 sheets into 1 package" << endl;
        sleep(2);

        sem_post(&semPaper);
        sem_post(&semPaper);
    }

    pthread_exit(nullptr);
    return nullptr;
}



int main() {
    pthread_t tidMakePaperA, tidMakePaperB, tidCombinePackage;
    int ret = 0;

    ret = sem_init(&semPackage, 0, 0);
    ret = sem_init(&semPaper, 0, 2);

    ret = pthread_create(&tidMakePaperA, nullptr, makeOnePaper, nullptr);
    ret = pthread_create(&tidMakePaperB, nullptr, makeOnePaper, nullptr);
    ret = pthread_create(&tidCombinePackage, nullptr, combineOnePackage, nullptr);

    ret = pthread_join(tidMakePaperA, nullptr);
    ret = pthread_join(tidMakePaperB, nullptr);
    ret = pthread_join(tidCombinePackage, nullptr);

    ret = sem_destroy(&semPackage);
    ret = sem_destroy(&semPaper);

    return 0;
}
