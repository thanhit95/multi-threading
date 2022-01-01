/*
GETTING RETURNED VALUES FROM THREADS
Version A: Values returned via pointers passed from arguments
*/


#include <iostream>
#include <pthread.h>
using namespace std;



struct ThreadArg {
    int value;
    int *res;
};



void* doubleValue(void* argVoid) {
    auto arg = (ThreadArg*) argVoid;

    *(arg->res) = arg->value * 2;

    pthread_exit(nullptr);
    return nullptr;
}



int main() {
    pthread_t tid;
    int result;
    ThreadArg arg;
    int ret = 0;

    arg = { 80, &result };

    ret = pthread_create(&tid, nullptr, doubleValue, &arg);
    ret = pthread_join(tid, nullptr);

    cout << result << endl;
    return 0;
}
