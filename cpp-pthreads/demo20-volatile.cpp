#include <iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;



volatile int stopped = false;



void* routine(void*) {
    while (false == stopped) {
        cout << "Running..." << endl;
        sleep(2);
    }

    pthread_exit(nullptr);
    return nullptr;
}



int main() {
    pthread_t tid;
    int ret = 0;

    ret = pthread_create(&tid, nullptr, routine, nullptr);

    sleep(6);

    stopped = true;

    ret = pthread_join(tid, nullptr);

    return 0;
}
