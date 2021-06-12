/*
When a thread is created, one of its attributes defines whether it is joinable or detached.
Only threads that are created as joinable can be joined.
If a thread is created as detached, it can never be joined.
*/


#include <iostream>
#include <pthread.h>
#include <unistd.h>

using namespace std;



void* routine(void *arg) {
    cout << "tid is starting..." << endl;

    sleep(2);

    cout << "tid is exiting..." << endl;

    pthread_exit(nullptr);
    return (void*)0;
}



int main() {
    pthread_t tid;
    int ret = 0;


    ret = pthread_create(&tid, nullptr, routine, nullptr);
    ret = pthread_detach(tid);

    if (ret) {
        cout << "error: cannot detach thread tid" << endl;
    }


    // ret = pthread_join(tid, nullptr);

    // if (ret) {
    //     cout << "error: cannot join thread tid" << endl;
    // }


    sleep(3); // if I comment this statement, the thread tid will be forced into terminating with main thread


    cout << "program is terminating" << endl;
    return 0;
}
