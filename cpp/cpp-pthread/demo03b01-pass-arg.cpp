/*
PASSING MULTIPLE ARGUMENTS
Solution 01: Creating a custom struct
*/


#include <iostream>
#include <string>
#include <pthread.h>
using namespace std;



struct ThreadArg {
    int x;
    double y;
    string z;
};



void* doTask(void* argVoid) {
    auto arg = (ThreadArg*) argVoid;

    cout << arg->x << endl;
    cout << arg->y << endl;
    cout << arg->z << endl;

    pthread_exit(nullptr);
    return nullptr;
}



int main() {
    pthread_t tid;
    ThreadArg arg;
    int ret = 0;

    arg.x = 10;
    arg.y = -2.4;
    arg.z = "lorem ipsum";

    ret = pthread_create(&tid, nullptr, doTask, &arg);
    ret = pthread_join(tid, nullptr);

    return 0;
}
