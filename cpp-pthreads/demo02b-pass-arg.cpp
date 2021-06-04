#include <iostream>
#include <pthread.h>

using namespace std;



void* printHello(void *p2id) {
    int id = *(int*)p2id;

    cout << "hello pthread with id = " << id << endl;

    pthread_exit(nullptr);
    return (void*)0;
}



int main() {
    constexpr int NUM_THREADS = 5;
    pthread_t tid[NUM_THREADS];
    int argThread[NUM_THREADS];


    for (int i = 0; i < NUM_THREADS; ++i) {
        cout << "creating thread " << i << endl;

        argThread[i] = i;

        pthread_create(&tid[i], nullptr, printHello, (void*)&argThread[i]);
    }


    // wait for all child threads until they finish
    for (int i = 0; i < NUM_THREADS; ++i)
        pthread_join(tid[i], nullptr);


    return 0;
}
