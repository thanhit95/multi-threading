/*
THREAD DETACHING
*/


#include <iostream>
#include <unistd.h>
#include <pthread.h>
using namespace std;



void* foo(void*) {
    int ret = 0;

    cout << "foo is starting..." << endl;

    if ( ret = pthread_detach(pthread_self()) ) {
        cout << "Error: Cannot detach" << endl;
    }

    sleep(2);

    cout << "foo is exiting..." << endl;

    pthread_exit(nullptr);
    return nullptr;
}



int main() {
    pthread_t tidFoo;
    int ret = 0;

    ret = pthread_create(&tidFoo, nullptr, &foo, nullptr);

    sleep(3);

    cout << "Main thread is exiting" << endl;
    return 0;
}
