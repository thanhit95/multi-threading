/*
THREAD DETACHING
*/


#include <iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;



void* routine(void *arg) {
    int ret = 0;

    cout << "Routine is starting..." << endl;

    if ( ret = pthread_detach(pthread_self()) ) {
        cout << "Error: Cannot detach routine" << endl;
    }

    sleep(2);

    cout << "Routine is exiting..." << endl;

    pthread_exit(nullptr);
    return nullptr;
}



int main() {
    pthread_t tid;
    int ret = 0;

    ret = pthread_create(&tid, nullptr, routine, nullptr);

    sleep(3);

    cout << "Program is terminating" << endl;
    return 0;
}
