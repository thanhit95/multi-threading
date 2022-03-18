/*
PASSING ARGUMENTS
Version A02: Solving the problem
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
    int lstArg[2];
    int ret = 0;

    for (int i = 0; i < 2; ++i) {
        lstArg[i] = i + 1;
        ret = pthread_create(&lstTid[i], nullptr, &doTask, &lstArg[i]);
    }

    for (int i = 0; i < 2; ++i)
        ret = pthread_join(lstTid[i], nullptr);

    return 0;
}
