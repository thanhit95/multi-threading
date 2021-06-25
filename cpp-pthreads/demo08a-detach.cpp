/*
DETACH
*/


#include <iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;



void* routine(void *arg) {
    cout << "Routine is starting..." << endl;

    sleep(2);

    cout << "Routine is exiting..." << endl;

    pthread_exit(nullptr);
    return nullptr;
}



int main() {
    pthread_t tid;
    int ret = 0;


    ret = pthread_create(&tid, nullptr, routine, nullptr);
    ret = pthread_detach(tid);

    if (ret) {
        cout << "Error: Cannot detach routine" << endl;
    }


    // ret = pthread_join(tid, nullptr);

    // if (ret) {
    //     cout << "Error: Cannot join routine" << endl;
    // }


    // If I comment this statement, the thread routine will be forced into terminating with main thread
    sleep(3);


    cout << "Program is terminating" << endl;
    return 0;
}
