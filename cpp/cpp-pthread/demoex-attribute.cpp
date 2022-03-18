#include <iostream>
#include <unistd.h>
#include <pthread.h>
using namespace std;



void* doTask(void* ptrId) {
    int id = *(int*)ptrId;

    cout << "Sleeping in thread " << id << endl;
    sleep(1);

    cout << "Thread with id " << id << " exiting..." << endl;

    pthread_exit(nullptr);
    return nullptr;
}



int main() {
    constexpr int NUM_THREADS = 3;

    pthread_t tid[NUM_THREADS];
    pthread_attr_t attr;
    int arg[NUM_THREADS];

    int ret = 0;

    // Initialize and set thread joinable
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE); // PTHREAD_CREATE_JOINABLE or PTHREAD_CREATE_DETACHED

    for (int i = 0; i < NUM_THREADS; ++i) {
        arg[i] = i;
        ret = pthread_create(&tid[i], &attr, &doTask, &arg[i]);
    }

    void* status = nullptr;

    for (int i = 0; i < NUM_THREADS; ++i) {
        ret = pthread_join(tid[i], &status);
        cout << "completed thread id " << i << " with status " << status << endl;
    }

    ret = pthread_attr_destroy(&attr);

    return 0;
}
