/*
GETTING THREAD'S ID
*/


#include <iostream>
#include <unistd.h>
#include <pthread.h>
using namespace std;



void* doTask(void*) {
    sleep(2);
    cout << pthread_self() << endl;

    pthread_exit(nullptr);
    return nullptr;
}



int main() {
    pthread_t tidFoo, tidBar;
    int ret = 0;

    ret = pthread_create(&tidFoo, nullptr, &doTask, nullptr);
    ret = pthread_create(&tidBar, nullptr, &doTask, nullptr);

    cout << "foo's id = " << tidFoo << endl;
    cout << "bar's id = " << tidBar << endl;

    ret = pthread_join(tidFoo, nullptr);
    ret = pthread_join(tidBar, nullptr);

    return 0;
}
