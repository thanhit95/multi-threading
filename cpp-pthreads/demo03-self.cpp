#include <iostream>
#include <pthread.h>

using namespace std;



void *routine(void *) {
    cout << "thread id is " << pthread_self() << endl;

    pthread_exit(nullptr);
    return (void*)0;
}



int main() {
    pthread_t tid1, tid2;
    int ret;

    ret = pthread_create(&tid1, nullptr, routine, nullptr);
    ret = pthread_create(&tid2, nullptr, routine, nullptr);

    ret = pthread_join(tid1, nullptr);
    ret = pthread_join(tid2, nullptr);

    cout << endl;
    cout << "tid1 = " << tid1 << endl;
    cout << "tid2 = " << tid2 << endl;

    return 0;
}
