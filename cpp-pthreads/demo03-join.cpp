/*
When a thread is created, one of its attributes defines whether it is joinable or detached.
Only threads that are created as joinable can be joined.
If a thread is created as detached, it can never be joined.
*/


#include <iostream>
#include <pthread.h>
#include <unistd.h>


using std::cout;
using std::endl;



void* printHello(void* p2id) {
    int id = *(int*)p2id;

    cout << "sleeping in thread " << id << endl, cout.flush();
    sleep(1);

    cout << "thread with id " << id << " exiting..." << endl, cout.flush();
    pthread_exit(nullptr);
}



int main(int argc, char **argv) {
    constexpr int NUM_THREADS = 3;
    pthread_t tid[NUM_THREADS];
    pthread_attr_t attr;
    int argThread[NUM_THREADS];


    // initialize and set thread joinable
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE); // PTHREAD_CREATE_JOINABLE or PTHREAD_CREATE_DETACHED


    for (int i = 0; i < NUM_THREADS; ++i) {
        argThread[i] = i;
        int ret = pthread_create(&tid[i], &attr, printHello, (void*)&argThread[i]);
    }


    void* status;

    for (int i = 0; i < NUM_THREADS; ++i) {
        int ret = pthread_join(tid[i], &status);
        cout << "completed thread id " << i << " with status " << status << endl, cout.flush();
    }


    pthread_attr_destroy(&attr);


    return 0;
}
