#include <iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;



void* routine(void *arg) {
    cout << "routine is starting..." << endl;

    sleep(2);

    cout << "routine is exiting..." << endl;

    pthread_exit(nullptr);
    return (void*)0;
}



int main() {
    pthread_t tid;
    int ret = 0;


    ret = pthread_create(&tid, nullptr, routine, nullptr);
    ret = pthread_detach(tid);

    if (ret) {
        cout << "error: cannot detach routine" << endl;
    }


    // ret = pthread_join(tid, nullptr);

    // if (ret) {
    //     cout << "error: cannot join routine" << endl;
    // }


    // If I comment this statement, the thread routine will be forced into terminating with main thread
    sleep(3);


    cout << "program is terminating" << endl;
    return 0;
}