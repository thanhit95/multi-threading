#include <iostream>
#include <pthread.h>


using std::cout;
using std::endl;



void *myFunc(void *param) {
    cout << "thread id is " << pthread_self() << endl;
    cout.flush();
    pthread_exit(nullptr);
}



int main(int argc, char **argv) {
    pthread_t tid1, tid2;
    int ret;

    ret = pthread_create(&tid1, nullptr, myFunc, nullptr);
    ret = pthread_create(&tid2, nullptr, myFunc, nullptr);

    ret = pthread_join(tid1, nullptr);
    ret = pthread_join(tid2, nullptr);

    cout << endl;
    cout << "tid1 = " << tid1 << endl;
    cout << "tid2 = " << tid2 << endl;

    return 0;
}
