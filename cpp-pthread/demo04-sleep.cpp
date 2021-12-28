/*
SLEEP
*/


#include <iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;



void* routine(void* arg) {
    auto name = (const char*)arg;

    cout << name << " is sleeping" << endl;
    sleep(2);
    cout << name << " wakes up" << endl;

    pthread_exit(nullptr);
    return nullptr;
}



int main() {
    pthread_t tid1, tid2;
    int ret = 0;

    ret = pthread_create(&tid1, nullptr, routine, (void*)"foo");
    ret = pthread_create(&tid2, nullptr, routine, (void*)"bar");

    ret = pthread_join(tid1, nullptr);
    ret = pthread_join(tid2, nullptr);

    return 0;
}
