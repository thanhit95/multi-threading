/*
ATOMIC ACCESS

In this demo, I use raw C language (not C++).
*/


#include <stdio.h>
#include <pthread.h>
#include <stdatomic.h> // C11 atomic
#include <unistd.h>



atomic_int counter;



void* doTask(void* arg) {
    sleep(1);
    atomic_fetch_add(&counter, 1);

    pthread_exit(NULL);
    return NULL;
}



int main() {
    atomic_store(&counter, 0); // assign counter = 0

    pthread_t lstTid[1000];
    int ret = 0;

    for (int i = 0; i < 1000; ++i) {
        ret = pthread_create(&lstTid[i], NULL, doTask, NULL);
    }

    for (int i = 0; i < 1000; ++i) {
        ret = pthread_join(lstTid[i], NULL);
    }

    // counter = 1000
    printf("counter = %d \n", counter);

    return 0;
}
