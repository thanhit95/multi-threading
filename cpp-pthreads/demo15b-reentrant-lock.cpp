/*
REENTRANT LOCK (RECURSIVE MUTEX)
*/


#include <iostream>
#include <pthread.h>
using namespace std;



pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;



int getFactorial(int n) {
    if (n <= 0)
        return 1;

    pthread_mutex_lock(&mut);

    int result = n * getFactorial(n - 1);

    pthread_mutex_unlock(&mut);

    return result;
}



void* routine(void* arg) {
    int n = *(int*)arg;

    int factorial = getFactorial(n);

    cout << "Factorial of " << n << " is " << factorial << endl;

    pthread_exit(nullptr);
    return (void*)0;
}



int main() {
    int n = 5;

    pthread_t tid;
    int ret = 0;

    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&mut, &attr);

    ret = pthread_create(&tid, nullptr, routine, (void*)&n);
    ret = pthread_join(tid, nullptr);

    pthread_mutexattr_destroy(&attr);
    pthread_mutex_destroy(&mut);

    return 0;
}
