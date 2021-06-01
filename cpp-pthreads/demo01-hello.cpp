#include <iostream>
#include <pthread.h>


using std::cout;
using std::cerr;
using std::endl;



void* hello_POSIX_thread(void *param) {
    char *message = (char*)param;
    cout << message << endl;
    cout.flush();
    return (void*)0;
}



int main(int argc, char **argv) {
    pthread_t tid1, tid2;

    char const* message1 = "thread 01";
    char const* message2 = "thread 02";

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
