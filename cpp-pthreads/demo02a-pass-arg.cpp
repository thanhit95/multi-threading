/*
PASSING ARGUMENTS - PROBLEM
    The id in statement "hello pthread with id = " might be DUPLICATED !!!
    Reason: Passing the address of variable i, so that all thread printHello use same value of i.
*/


#include <iostream>
#include <pthread.h>
using namespace std;



void* printHello(void* ptrId) {
    int id = *(int*)ptrId;

    cout << "Hello pthread with id = " << id << endl;

    pthread_exit(nullptr);
    return (void*)0;
}



int main() {
    pthread_t tid[2];
    int ret = 0;


    for (int i = 0; i < 2; ++i)
        ret = pthread_create(&tid[i], nullptr, printHello, &i);


    for (int i = 0; i < 2; ++i)
        ret = pthread_join(tid[i], nullptr);


    return 0;
}
