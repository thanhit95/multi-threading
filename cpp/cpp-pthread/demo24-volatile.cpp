/*
THE VOLATILE KEYWORD
*/


#include <iostream>
#include <unistd.h>
#include <pthread.h>
using namespace std;



volatile bool isRunning;



void* doTask(void*) {
    while (isRunning) {
        cout << "Running..." << endl;
        sleep(2);
    }

    pthread_exit(nullptr);
    return nullptr;
}



int main() {
    pthread_t tid;
    int ret = 0;

    isRunning = true;
    ret = pthread_create(&tid, nullptr, &doTask, nullptr);

    sleep(6);
    isRunning = false;

    ret = pthread_join(tid, nullptr);
    return 0;
}
