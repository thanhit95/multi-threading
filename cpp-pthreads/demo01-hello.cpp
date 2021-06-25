/*
HELLO WORLD VERSION MULTITHREADING
*/


#include <iostream>
#include <pthread.h>
using namespace std;



void* helloThread(void* arg) {
    cout << "Hello" << endl;

    pthread_exit(nullptr);
    return nullptr;
}



int main() {
    pthread_t tid1, tid2;
    int ret = 0;

    ret = pthread_create(&tid1, nullptr, helloThread, nullptr);
    ret = pthread_create(&tid2, nullptr, helloThread, nullptr);

    /*
    if (ret) {
        cerr << "Error: Unable to create thread" << ret << endl;
    }
    */

    ret = pthread_join(tid1, nullptr);
    ret = pthread_join(tid2, nullptr);

    return 0;
}
