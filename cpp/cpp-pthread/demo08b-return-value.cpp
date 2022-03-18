/*
GETTING RETURNED VALUES FROM THREADS
Version B: Values returned via pthread_exit
*/


#include <iostream>
#include <pthread.h>
using namespace std;



void* doubleValue(void* arg) {
    auto value = *(int*) arg;

    int *result = new int;
    *result = value * 2;

    pthread_exit((void*)result);
    return (void*)result;
}



int main() {
    pthread_t tid;
    int arg = 80;
    int *result = nullptr;
    int ret = 0;

    ret = pthread_create(&tid, nullptr, &doubleValue, &arg);
    ret = pthread_join(tid, (void**)&result);

    cout << (*result) << endl;

    delete result;
    result = nullptr;

    return 0;
}
