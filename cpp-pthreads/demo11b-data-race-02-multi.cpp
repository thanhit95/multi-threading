/*
DATA RACE
Version 02: Multithreading
*/


#include <iostream>
#include <cstdlib>
#include <pthread.h>
using namespace std;



int *a = nullptr;
int N = 0;



void* markDiv2(void*) {
    for (int i = 2; i <= N; i += 2)
        a[i] = 1;

    pthread_exit(nullptr);
    return nullptr;
}



void* markDiv3(void*) {
    for (int i = 3; i <= N; i += 3)
        a[i] = 1;

    pthread_exit(nullptr);
    return nullptr;
}



int main() {
    N = 8;

    pthread_t tidDiv2, tidDiv3;
    int ret = 0;


    a = (int*)calloc(sizeof(int), N + 1);


    ret = pthread_create(&tidDiv2, nullptr, markDiv2, nullptr);
    ret = pthread_create(&tidDiv3, nullptr, markDiv3, nullptr);
    ret = pthread_join(tidDiv2, nullptr);
    ret = pthread_join(tidDiv3, nullptr);


    int result = 0;

    for (int i = 1; i <= N; ++i)
        if (a[i] == 1)
            ++result;


    free(a);
    a = nullptr;


    cout << "Numbers of integers that are divisible by 2 or 3 is: " << result << endl;
    return 0;
}
