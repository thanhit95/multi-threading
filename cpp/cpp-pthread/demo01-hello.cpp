/*
HELLO WORLD VERSION MULTITHREADING
*/


#include <iostream>
#include <pthread.h>
using namespace std;



void* doTask(void*) {
    cout << "Hello from example thread" << endl;

    pthread_exit(nullptr);
    return nullptr;
}



int main() {
    pthread_t tid;
    int ret = 0;

    ret = pthread_create(&tid, nullptr, &doTask, nullptr);

    /*
    if (ret) {
        cerr << "Error: Unable to create thread " << ret << endl;
        return 1;
    }
    */

    ret = pthread_join(tid, nullptr);
    return 0;
}
