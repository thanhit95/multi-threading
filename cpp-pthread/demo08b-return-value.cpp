/*
GETTING RETURNED VALUES FROM THREADS
Version A: Values returned via pthread_exit
*/


#include <iostream>
#include <pthread.h>
using namespace std;



void* worker(void* argVoid) {
    auto value = *(int*)argVoid;

    int *result = new int;
    *result = value * 2;

    pthread_exit((void*)result);
    return (void*)result;
}



int main() {
    int arg0 = 5, arg1 = 80;
    int *result0 = nullptr, *result1 = nullptr;

    pthread_t tid0, tid1;
    int ret = 0;


    ret = pthread_create(&tid0, nullptr, worker, &arg0);
    ret = pthread_create(&tid1, nullptr, worker, &arg1);

    ret = pthread_join(tid0, (void**)&result0);
    ret = pthread_join(tid1, (void**)&result1);


    cout << (*result0) << endl;
    cout << (*result1) << endl;


    delete result0, result1;
    result0 = result1 = nullptr;

    return 0;
}
