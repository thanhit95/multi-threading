/*
THREAD JOINS
*/


#include <iostream>
#include <pthread.h>
using namespace std;



void* doHeavyTask(void*) {
    // Do a heavy task, which takes a little time
    for (int i = 0; i < 2000000000; ++i);

    cout << "Done!" << endl;

    pthread_exit(nullptr);
    return nullptr;
}



int main() {
    pthread_t tid;
    int ret = 0;

    ret = pthread_create(&tid, nullptr, doHeavyTask, nullptr);

    ret = pthread_join(tid, nullptr);

    cout << "Good bye!" << endl;

    return 0;
}
