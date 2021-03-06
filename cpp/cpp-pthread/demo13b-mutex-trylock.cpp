/*
MUTEXES
Locking with a nonblocking mutex

Use pthread_mutex_trylock to attempt to lock the mutex pointed to by mutex.
*/


#include <iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;



pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
int counter = 0;



void* doTask(void*) {
    int ret = 0;
    sleep(1);

    ret = pthread_mutex_trylock(&mut);

    if (ret) {
        /*
        switch (ret) {
            case EBUSY:
                The mutex could not be acquired because the mutex pointed to by mutex
                was already locked.

            case EAGAIN:
                The mutex could not be acquired because the maximum number
                of recursive locks for mutex has been exceeded.

            case EOWNERDEAD:
                The last owner of this mutex died while holding the mutex.
                This mutex is now owned by the caller.
                The caller must attempt to make the state protected by the mutex consistent.

            case ENOTRECOVERABLE:
                The mutex you are trying to acquire is protecting state left irrecoverable
                by the mutex's previous owner that died while holding the lock.
                The mutex has not been acquired.
                This condition can occur when the lock was previously acquired
                with EOWNERDEAD and the owner was unable to cleanup the state and
                had unlocked the mutex without making the mutex state consistent.

            case ENOMEM:
                The limit on the number of simultaneously held mutexes has been exceeded.
        }
        */

        pthread_exit(nullptr);
        return nullptr;
    }

    for (int i = 0; i < 10000; ++i)
        ++counter;

    pthread_mutex_unlock(&mut);

    pthread_exit(nullptr);
    return nullptr;
}



int main() {
    constexpr int NUM_THREADS = 3;
    pthread_t lstTid[NUM_THREADS];
    int ret = 0;

    for (auto&& tid : lstTid) {
        ret = pthread_create(&tid, nullptr, &doTask, nullptr);
    }

    for (auto&& tid : lstTid) {
        ret = pthread_join(tid, nullptr);
    }

    cout << "counter = " << counter << endl;
    // counter can be 10000, 20000 or 30000

    ret = pthread_mutex_destroy(&mut);
    return 0;
}
