/*
PASSING ARGUMENTS
Version A01: The problem

The id in statement "hello pthread with id..." might be DUPLICATED!!!
Reason: Passing the address of variable i,
        so that all threads use a same value of i.
*/


#include <iostream>
#include <pthread.h>
using namespace std;



void* doTask(void* ptrId) {
    int id = *(int*)ptrId;

    cout << "Hello pthread with id = " << id << endl;

    pthread_exit(nullptr);
    return nullptr;
}



int main() {
    pthread_t lstTid[2];
    int ret = 0;

    for (int i = 0; i < 2; ++i)
        ret = pthread_create(&lstTid[i], nullptr, &doTask, &i);

    for (int i = 0; i < 2; ++i)
        ret = pthread_join(lstTid[i], nullptr);

    return 0;
}
