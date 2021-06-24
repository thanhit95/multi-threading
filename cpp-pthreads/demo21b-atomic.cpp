/*
In this demo, I use raw C language (not C++).
*/


#include <stdio.h>
#include <pthread.h>
#include <stdatomic.h> // C11 atomic
#include <unistd.h>



atomic_int counter;



void* routine(void* arg) {
    sleep(1);
    atomic_fetch_add(&counter, 1);

    pthread_exit(NULL);
    return NULL;
}



int main() {
    pthread_t tidA, tidB;
    int ret = 0;

    atomic_init(&counter, 0);

    ret = pthread_create(&tidA, NULL, routine, NULL);
    ret = pthread_create(&tidB, NULL, routine, NULL);

    ret = pthread_join(tidA, NULL);
    ret = pthread_join(tidB, NULL);

    printf("counter = %d \n", counter); // counter = 2
    return 0;
}
