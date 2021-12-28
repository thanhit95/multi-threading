/*
THREAD JOINING
*/


#include <iostream>
#include <pthread.h>
using namespace std;



void* threadFunc(void*) {
    // Doing a heavy task...
    for (int i = 0; i < 1000000000; ++i);

    cout << "First" << endl;

    pthread_exit(nullptr);
    return nullptr;
}



int main() {
    pthread_t tid;
    int ret = 0;

    ret = pthread_create(&tid, nullptr, threadFunc, nullptr);

    ret = pthread_join(tid, nullptr);

    cout << "Second" << endl;

    return 0;
}
