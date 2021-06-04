#include <iostream>
#include <pthread.h>

using namespace std;



void* hello_POSIX_thread(void *arg) {
    char *message = (char*)arg;
    cout << message << endl;

    // pthread_exit(nullptr);
    return (void*)0;
}



int main() {
    pthread_t tid1, tid2;

    char const* message1 = "thread 1";
    char const* message2 = "thread 2";

    int ret;

    ret = pthread_create(&tid1, nullptr, hello_POSIX_thread, (void*)message1);
    ret = pthread_create(&tid2, nullptr, hello_POSIX_thread, (void*)message2);

    /*
    if (ret) {
        cerr << "error: unable to create thread" << ret << endl;
    }
    */

    ret = pthread_join(tid1, nullptr);
    ret = pthread_join(tid2, nullptr);

    return 0;
}
