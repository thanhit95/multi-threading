/*
In this demo, I use raw C language (not C++).
*/


#include <stdio.h>
#include <pthread.h>
#include <unistd.h>



volatile int counter = 0;



void* routine(void* arg) {
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

    printf("counter = %d \n", counter); // unpredictable result
    return 0;
}
