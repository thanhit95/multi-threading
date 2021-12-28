/*
GETTING THREAD ID
*/


#include <iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;



void* routine(void*) {
    sleep(2);
    cout << "Thread id is " << pthread_self() << endl;

    pthread_exit(nullptr);
    return nullptr;
}



int main() {
    pthread_t tid1, tid2;
    int ret = 0;

    ret = pthread_create(&tid1, nullptr, routine, nullptr);
    ret = pthread_create(&tid2, nullptr, routine, nullptr);

    cout << "tid1 = " << tid1 << endl;
    cout << "tid2 = " << tid2 << endl;

    ret = pthread_join(tid1, nullptr);
    ret = pthread_join(tid2, nullptr);

    return 0;
}
