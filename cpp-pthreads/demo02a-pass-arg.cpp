/*
Compile with this command
    g++ -o a demo01.cpp -lpthread

PROBLEM
    The id in statement "hello pthread with id = " is DUPLICATED !!!
    Reason: Passing the address of variable i, so that all thread printHello use same value of i.
*/


#include <iostream>
#include <pthread.h>


using std::cout;
using std::endl;



void* printHello(void *p2id) {
    int id = *(int*)p2id;

    cout << "hello pthread with id = " << id << endl;
    cout.flush();

    pthread_exit(nullptr);
}



int main(int argc, char **argv) {
    constexpr int NUM_THREADS = 5;
    pthread_t tid[NUM_THREADS];


    for (int i = 0; i < NUM_THREADS; ++i) {
        cout << "creating thread " << i << endl;
        cout.flush();

        int ret = pthread_create(&tid[i], nullptr, printHello, (void*)&i);
    }


    // wait for all child threads until they finish
    for (int i = 0; i < NUM_THREADS; ++i)
        pthread_join(tid[i], nullptr);


    return 0;
}
