#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
using namespace std;



void signalHandler(int sig) {
    cout << "caught signal " << sig << endl;
    // signal(SIGSEGV, signalHandler);
}



void* func(void* arg) {
    cout << "foo" << endl;
    sleep(5);

    pthread_exit(nullptr);
    return nullptr;
}



int main() {
    pthread_t tid;

    signal(SIGSEGV, signalHandler); // register signal handler before going multithread

    pthread_create(&tid, nullptr, func, nullptr);
    sleep(1); // leave time for initialization

    pthread_kill(tid, SIGSEGV);

    pthread_join(tid, NULL);

    cout << "bar" << endl;
    return 0;
}
