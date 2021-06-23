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
    int arg[2];

    int ret = 0;


    for (int i = 0; i < 2; ++i) {
        arg[i] = i + 1;
        ret = pthread_create(&tid[i], nullptr, printHello, &arg[i]);
    }


    for (int i = 0; i < 2; ++i)
        ret = pthread_join(tid[i], nullptr);


    return 0;
}
