/*
GETTING RETURNED VALUES FROM THREADS
Version A: Values returned via pointers passed from arguments
*/


#include <iostream>
#include <pthread.h>
using namespace std;



struct WorkerArg {
    int value;
    int *res;
};



void* worker(void* argVoid) {
    auto arg = (WorkerArg*)argVoid;

    *(arg->res) = arg->value * 2;

    pthread_exit(nullptr);
    return nullptr;
}



int main() {
    int result[2];
    WorkerArg arg[2];

    pthread_t tid0, tid1;
    int ret = 0;


    arg[0] = { 5, &result[0] };
    arg[1] = { 80, &result[1] };


    ret = pthread_create(&tid0, nullptr, worker, &arg[0]);
    ret = pthread_create(&tid1, nullptr, worker, &arg[1]);

    ret = pthread_join(tid0, nullptr);
    ret = pthread_join(tid1, nullptr);


    cout << result[0] << endl;
    cout << result[1] << endl;

    return 0;
}
