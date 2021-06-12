#include <iostream>
#include <pthread.h>

using namespace std;



class Task {
private:
    pthread_t tid;
public:
    int index;


public:
    Task(const Task &other) = delete;
    Task(const Task &&other) = delete;
    void operator=(const Task &other) = delete;
    void operator=(const Task &&other) = delete;


    Task(int index = -1): index(index) {

    }


    int start() {
        int ret = pthread_create(&tid, nullptr, work, (void*)this);
        return ret;
    }


    int join() {
        int ret = pthread_join(tid, nullptr);
        return ret;
    }


private:
    static void* work(void *arg) {
        auto thisPtr = (Task*)arg;

        cout << thisPtr->index << endl;

        pthread_exit(nullptr);
        return (void*)0;
    }
};



int main() {
    constexpr int NUM_TASKS = 3;
    Task task[NUM_TASKS];


    for (int i = 0; i < NUM_TASKS; ++i) {
        task[i].index = i;
    }


    for (int i = 0; i < NUM_TASKS; ++i) {
        task[i].start();
    }


    for (int i = 0; i < NUM_TASKS; ++i) {
        task[i].join();
    }

    return 0;
}
