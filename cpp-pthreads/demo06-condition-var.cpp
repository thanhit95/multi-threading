#include <iostream>
#include <pthread.h>
using namespace std;



pthread_mutex_t countMutex = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t conditionVariable = PTHREAD_COND_INITIALIZER;

int count = 0;
constexpr int COUNT_HALT_01 = 3;
constexpr int COUNT_HALT_02 = 6;
constexpr int COUNT_DONE = 10;



// write numbers 1-3 and 8-10 as permitted by funcB()
void* funcA(void *) {
    for (;;) {
        // lock mutex and then wait for signal to relase mutex
        pthread_mutex_lock(&countMutex);

        // wait while funcB() operates on count,
        // mutex unlocked if condition variable in funcB() signaled
        pthread_cond_wait(&conditionVariable, &countMutex);

        ++count;
        cout << "funcA count = " << count << endl, cout.flush();

        pthread_mutex_unlock(&countMutex);

        if (count >= COUNT_DONE) {
            pthread_exit(nullptr);
            return (void*)0;
        }
    }

    pthread_exit(nullptr);
    return (void*)0;
}


// write numbers 4-7
void* funcB(void *) {
    for (;;) {
        pthread_mutex_lock(&countMutex);

        if (count < COUNT_HALT_01 || count > COUNT_HALT_02) {
            // signal to free waiting thread by freeing the mutex
            // note: funcA() is now permitted to modify "count"
            pthread_cond_signal(&conditionVariable);
        }
        else {
            ++count;
            cout << "funcB count = " << count << endl, cout.flush();
        }

        pthread_mutex_unlock(&countMutex);

        if (count >= COUNT_DONE) {
            pthread_exit(nullptr);
            return (void*)0;
        }
    }

    pthread_exit(nullptr);
    return (void*)0;
}



int main() {
    pthread_t tid1, tid2;
    int ret;

    ret = pthread_create(&tid1, nullptr, funcA, nullptr);
    ret = pthread_create(&tid2, nullptr, funcB, nullptr);

    ret = pthread_join(tid1, nullptr);
    ret = pthread_join(tid2, nullptr);

    ret = pthread_mutex_destroy(&countMutex);

    return 0;
}
