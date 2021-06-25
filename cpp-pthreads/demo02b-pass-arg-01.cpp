/*
PASSING MULTIPLE ARGUMENTS IN PTHREADS
Solution 01: Creating a custom struct
*/


#include <iostream>
#include <string>
#include <pthread.h>
using namespace std;



struct RoutineArg {
    int x;
    double y;
    string z;
};



void* routine(void* argVoid) {
    auto arg = (RoutineArg*)argVoid;

    cout << arg->x << endl;
    cout << arg->y << endl;
    cout << arg->z << endl;

    pthread_exit(nullptr);
    return nullptr;
}



int main() {
    pthread_t tid;
    RoutineArg arg;

    int ret = 0;


    arg.x = 10;
    arg.y = -2.4;
    arg.z = "barrrrr";


    ret = pthread_create(&tid, nullptr, routine, &arg);
    ret = pthread_join(tid, nullptr);


    return 0;
}
