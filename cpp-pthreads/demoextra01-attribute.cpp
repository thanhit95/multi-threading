#include <iostream>
#include <pthread.h>
#include <unistd.h>

using namespace std;



void* routine(void *p2id) {
    int id = *(int*)p2id;

    cout << "sleeping in thread " << id << endl;
    sleep(1);

    cout << "thread with id " << id << " exiting..." << endl;

    pthread_exit(nullptr);
    return (void*)0;
}



int main() {
    constexpr int NUM_THREADS = 3;

    pthread_t tid[NUM_THREADS];
    pthread_attr_t attr;
    int argThread[NUM_THREADS];


    // initialize and set thread joinable
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE); // PTHREAD_CREATE_JOINABLE or PTHREAD_CREATE_DETACHED


    for (int i = 0; i < NUM_THREADS; ++i) {
        argThread[i] = i;
        int ret = pthread_create(&tid[i], &attr, routine, (void*)&argThread[i]);
    }


    void* status;

    for (int i = 0; i < NUM_THREADS; ++i) {
        int ret = pthread_join(tid[i], &status);
        cout << "completed thread id " << i << " with status " << status << endl;
    }


    pthread_attr_destroy(&attr);


    return 0;
}
