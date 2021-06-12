#include <iostream>
#include <pthread.h>
#include <unistd.h>

using namespace std;



void* routine(void *arg) {
    int ret = 0;

    cout << "tid is starting..." << endl;

    if ( ret = pthread_detach(pthread_self()) ) {
        cout << "error: cannot detach thread tid" << endl;
    }

    sleep(2);

    cout << "tid is exiting..." << endl;

    pthread_exit(nullptr);
    return (void*)0;
}



int main() {
    pthread_t tid;
    int ret = 0;

    ret = pthread_create(&tid, nullptr, routine, nullptr);

    sleep(3);

    cout << "program is terminating" << endl;
    return 0;
}
