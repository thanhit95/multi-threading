/*
THREAD DETACHING
*/


#include <iostream>
#include <unistd.h>
#include <pthread.h>
using namespace std;



void* foo(void*) {
    cout << "foo is starting..." << endl;

    sleep(2);

    cout << "foo is exiting..." << endl;

    pthread_exit(nullptr);
    return nullptr;
}



int main() {
    pthread_t tidFoo;
    int ret = 0;


    ret = pthread_create(&tidFoo, nullptr, &foo, nullptr);
    ret = pthread_detach(tidFoo);

    if (ret) {
        cout << "Error: Cannot detach tidFoo" << endl;
    }


    // ret = pthread_join(tidFoo, nullptr);
    // if (ret) {
    //     cout << "Error: Cannot join tidFoo" << endl;
    // }


    // If I comment this statement,
    // tidFoo will be forced into terminating with main thread
    sleep(3);


    cout << "Main thread is exiting" << endl;
    return 0;
}
