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
    pthread_t lstTid[1000];
    int ret = 0;

    for (int i = 0; i < 1000; ++i) {
        ret = pthread_create(&lstTid[i], NULL, routine, NULL);
    }

    for (int i = 0; i < 1000; ++i) {
        ret = pthread_join(lstTid[i], NULL);
    }

    // Unpredictable result
    printf("counter = %d \n", counter);

    return 0;
}
