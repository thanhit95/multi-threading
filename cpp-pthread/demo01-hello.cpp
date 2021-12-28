/*
HELLO WORLD VERSION MULTITHREADING
*/


#include <iostream>
#include <pthread.h>
using namespace std;



void* lorem(void*) {
    cout << "Hello from Lorem thread" << endl;

    pthread_exit(nullptr);
    return nullptr;
}



int main() {
    pthread_t tid;
    int ret = 0;

    ret = pthread_create(&tid, nullptr, lorem, nullptr);

    /*
    if (ret) {
        cerr << "Error: Unable to create thread " << ret << endl;
    }
    */

    ret = pthread_join(tid, nullptr);
    return 0;
}
