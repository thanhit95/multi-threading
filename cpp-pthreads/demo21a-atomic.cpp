/*
ATOMIC
In this demo, I use raw C language (not C++).
*/


#include <stdio.h>
#include <pthread.h>
#include <unistd.h>



volatile int counter = 0;



void* routine(void* arg) {
    sleep(1);
    counter += 1;

    pthread_exit(NULL);
    return NULL;
}



int main() {
    pthread_t tidA, tidB;
    int ret = 0;

    ret = pthread_create(&tidA, NULL, routine, NULL);
    ret = pthread_create(&tidB, NULL, routine, NULL);

    ret = pthread_join(tidA, NULL);
    ret = pthread_join(tidB, NULL);

    printf("counter = %d \n", counter); // unpredictable result
    return 0;
}
