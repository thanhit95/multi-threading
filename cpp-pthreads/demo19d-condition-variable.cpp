#include <iostream>
#include <pthread.h>
using namespace std;



pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t conditionVar = PTHREAD_COND_INITIALIZER;

int counter = 0;

constexpr int COUNT_HALT_01 = 3;
constexpr int COUNT_HALT_02 = 6;
constexpr int COUNT_DONE = 10;



// Write numbers 1-3 and 8-10 as permitted by eggs()
void* foo(void*) {
    for (;;) {
        // Lock mutex and then wait for signal to relase mutex
        pthread_mutex_lock(&mut);

        // Wait while eggs() operates on counter,
        // Mutex unlocked if condition variable in eggs() signaled
        pthread_cond_wait(&conditionVar, &mut);

        ++counter;
        cout << "foo count = " << counter << endl;

        pthread_mutex_unlock(&mut);

        if (counter >= COUNT_DONE) {
            pthread_exit(nullptr);
            return nullptr;
        }
    }

    pthread_exit(nullptr);
    return nullptr;
}



// Write numbers 4-7
void* eggs(void*) {
    for (;;) {
        pthread_mutex_lock(&mut);

        if (counter < COUNT_HALT_01 || counter > COUNT_HALT_02) {
            // Signal to free waiting thread by freeing the mutex
            // Note: foo() is now permitted to modify "counter"
            pthread_cond_signal(&conditionVar);
        }
        else {
            ++counter;
            cout << "eggs counter = " << counter << endl;
        }

        pthread_mutex_unlock(&mut);

        if (counter >= COUNT_DONE) {
            pthread_exit(nullptr);
            return nullptr;
        }
    }

    pthread_exit(nullptr);
    return nullptr;
}



int main() {
    pthread_t tidFoo, tidEggs;
    int ret = 0;

    ret = pthread_create(&tidFoo, nullptr, foo, nullptr);
    ret = pthread_create(&tidEggs, nullptr, eggs, nullptr);

    ret = pthread_join(tidFoo, nullptr);
    ret = pthread_join(tidEggs, nullptr);

    ret = pthread_cond_destroy(&conditionVar);
    ret = pthread_mutex_destroy(&mut);

    return 0;
}
