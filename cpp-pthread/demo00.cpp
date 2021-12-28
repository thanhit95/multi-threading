/*
INTRODUCTION TO MULTITHREADING
You should try running this app several times and see results.
*/


#include <iostream>
#include <pthread.h>
using namespace std;



void* threadFunc(void*) {
    for (int i = 0; i < 300; ++i)
        cout << "B";

    pthread_exit(nullptr);
    return nullptr;
}



int main() {
    pthread_t tid;
    int ret = 0;

    ret = pthread_create(&tid, nullptr, threadFunc, nullptr);

    for (int i = 0; i < 300; ++i)
        cout << "A";

    ret = pthread_join(tid, nullptr);

    cout << endl;
    return 0;
}
