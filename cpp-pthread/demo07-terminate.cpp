/*
FORCING A THREAD TO TERMINATE (i.e. killing the thread)
*/


#include <iostream>
#include <unistd.h>
#include <pthread.h>
using namespace std;



void* doTask(void*) {
    while (1) {
        cout << "Running..." << endl;
        sleep(1);
    }

    pthread_exit(nullptr);
    return nullptr;
}



int main() {
    pthread_t tid;
    int ret = 0;

    ret = pthread_create(&tid, nullptr, doTask, nullptr);

    sleep(3);

    ret = pthread_cancel(tid);

    ret = pthread_join(tid, nullptr);

    return 0;
}
