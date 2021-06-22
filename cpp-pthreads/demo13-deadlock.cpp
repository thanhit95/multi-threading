/*
DEADLOCK DEMONSTRATION

There are 2 workers "foo" and "bar".
They try to access resource A and B (following by mutResourceA and mutResourceB).

foo():
    synchronized:
        access resource A

        synchronized:
            access resource B


bar():
    synchronized:
        access resource B

        synchronized:
            access resource A


After first time accessing resource, foo and bar will wait other together ==> Deadlock occurs.
*/


#include <iostream>
#include <pthread.h>
#include <unistd.h>

using namespace std;



struct GlobalArg {
    pthread_mutex_t mutResourceA = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_t mutResourceB = PTHREAD_MUTEX_INITIALIZER;
    char const* resourceA;
    char const* resourceB;
};



void* foo(void *argVoid) {
    auto arg = (GlobalArg*)argVoid;

    pthread_mutex_lock(&arg->mutResourceA);
    cout << "foo enters resource A" << endl;

    sleep(1);

    pthread_mutex_lock(&arg->mutResourceB);
    cout << "foo enters resource B" << endl;
    pthread_mutex_unlock(&arg->mutResourceB);

    pthread_mutex_unlock(&arg->mutResourceA);

    pthread_exit(nullptr);
    return (void*)0;
}



void* bar(void *argVoid) {
    auto arg = (GlobalArg*)argVoid;

    pthread_mutex_lock(&arg->mutResourceB);
    cout << "bar enters resource B" << endl;

    sleep(1);

    pthread_mutex_lock(&arg->mutResourceA);
    cout << "bar enters resource A" << endl;
    pthread_mutex_unlock(&arg->mutResourceA);

    pthread_mutex_unlock(&arg->mutResourceB);

    pthread_exit(nullptr);
    return (void*)0;
}



int main() {
    pthread_t tid1, tid2;
    GlobalArg arg;

    char const* resourceA = "This is resource A";
    char const* resourceB = "This is resource B";
    arg.resourceA = resourceA;
    arg.resourceB = resourceB;

    int ret;


    ret = pthread_create(&tid1, nullptr, foo, (void*)&arg);
    ret = pthread_create(&tid2, nullptr, bar, (void*)&arg);


    ret = pthread_join(tid1, nullptr);
    ret = pthread_join(tid2, nullptr);


    ret = pthread_mutex_destroy(&arg.mutResourceA);
    ret = pthread_mutex_destroy(&arg.mutResourceB);


    cout << "You will never see this statement due to deadlock!" << endl;
    return 0;
}
