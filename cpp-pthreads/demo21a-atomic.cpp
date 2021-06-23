#include <iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;



volatile int counter = 0;



void* routine(void*) {
    sleep(1);
    counter += 1;

    pthread_exit(nullptr);
    return (void*)0;
}



int main() {
    pthread_t tidA, tidB;
    int ret = 0;

    ret = pthread_create(&tidA, nullptr, routine, nullptr);
    ret = pthread_create(&tidB, nullptr, routine, nullptr);

    ret = pthread_join(tidA, nullptr);
    ret = pthread_join(tidB, nullptr);

    cout << "counter = " << counter << endl; // unpredictable result
    return 0;
}
