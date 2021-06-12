/*
SEMAPHORE

In an exam, each candidate is given a couple of 2 scratch papers.
Write a program to illustrate this scene.
The program will combine 2 scratch papers into one test package, concurrenly.

This version 03 is slightly different:
    - There are 2 production lines of making scratch papers (i.e. 2 threads).
    - There is 1 production lines of making test packages (i.e. 1 thread).


The problem in this version is DEADLOCK.
*/


#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

using namespace std;



sem_t semPaper;
sem_t semPackage;



void* makeOnePaper(void *) {
    for (int i = 0; i < 5; ++i) {
        sem_wait(&semPackage);

        cout << "make 1 paper" << endl;
        sem_post(&semPaper);
    }

    pthread_exit(nullptr);
    return (void*)0;
}



void* combineOnePackage(void *) {
    for (int i = 0; i < 5; ++i) {
        sem_wait(&semPaper);
        sem_wait(&semPaper);

        cout << "combine 2 papers into 1 package" << endl;
        sleep(2);

        sem_post(&semPackage);
        // missing one statement: sem_post(&semPackage) ==> DEADLOCK
    }

    pthread_exit(nullptr);
    return (void*)0;
}



int main() {
    pthread_t tidMakePaperA, tidMakePaperB, tidCombinePackage;
    int ret = 0;

    ret = sem_init(&semPaper, 0, 0);
    ret = sem_init(&semPackage, 0, 2);

    ret = pthread_create(&tidMakePaperA, nullptr, makeOnePaper, nullptr);
    ret = pthread_create(&tidMakePaperB, nullptr, makeOnePaper, nullptr);
    ret = pthread_create(&tidCombinePackage, nullptr, combineOnePackage, nullptr);

    ret = pthread_join(tidMakePaperA, nullptr);
    ret = pthread_join(tidMakePaperB, nullptr);
    ret = pthread_join(tidCombinePackage, nullptr);

    ret = sem_destroy(&semPaper);
    ret = sem_destroy(&semPackage);

    return 0;
}
