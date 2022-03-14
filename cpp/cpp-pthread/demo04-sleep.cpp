/*
SLEEP
*/


#include <iostream>
#include <unistd.h>
#include <pthread.h>
using namespace std;



void* doTask(void* arg) {
    auto name = (const char*) arg;

    cout << name << " is sleeping" << endl;
    sleep(2);
    cout << name << " wakes up" << endl;

    pthread_exit(nullptr);
    return nullptr;
}



int main() {
    pthread_t tid;
    int ret = 0;

    ret = pthread_create(&tid, nullptr, doTask, (void*)"foo");

    ret = pthread_join(tid, nullptr);

    return 0;
}
