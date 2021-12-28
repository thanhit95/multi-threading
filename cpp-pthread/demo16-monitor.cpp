/*
MONITORS
Implementation of a monitor
*/


#include <iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;



class Monitor {
private:
    pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
    int* pCounter = nullptr;


public:
    void init(int* pCounter) {
        destroy();
        mut = PTHREAD_MUTEX_INITIALIZER;
        this->pCounter = pCounter;
    }


    void increaseCounter() {
        int ret = 0;

        ret = pthread_mutex_lock(&mut);

        (*pCounter) += 1;

        ret = pthread_mutex_unlock(&mut);
    }


    void destroy() {
        pthread_mutex_destroy(&mut);
    }
};



void* routineCounter(void* arg) {
    auto monitor = (Monitor*)arg;

    sleep(1);

    for (int i = 0; i < 1000; ++i)
        monitor->increaseCounter();

    pthread_exit(nullptr);
    return nullptr;
}



int main() {
    int counter = 0;
    Monitor monitor;

    constexpr int NUM_THREADS = 3;
    pthread_t lstTid[NUM_THREADS];

    int ret = 0;


    monitor.init(&counter);


    for (auto&& tid : lstTid) {
        ret = pthread_create(&tid, nullptr, routineCounter, &monitor);
    }


    for (auto&& tid : lstTid) {
        ret = pthread_join(tid, nullptr);
    }


    monitor.destroy();


    cout << "counter = " << counter << endl;
    return 0;
}
