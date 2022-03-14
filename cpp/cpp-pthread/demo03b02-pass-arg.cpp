/*
PASSING MULTIPLE ARGUMENTS
Solution 02: Using std::tuple
*/


#include <iostream>
#include <string>
#include <tuple>
#include <pthread.h>
using namespace std;



void* doTask(void* argVoid) {
    auto arg = * (tuple<int,double,string> *) argVoid;

    cout << std::get<0>(arg) << endl;
    cout << std::get<1>(arg) << endl;
    cout << std::get<2>(arg) << endl;

    pthread_exit(nullptr);
    return nullptr;
}



int main() {
    pthread_t tid;
    tuple<int,double,string> arg;
    int ret = 0;

    // arg = std::make_tuple( 10, -2.4, "lorem ipsum" );
    arg = { 10, -2.4, "lorem ipsum" };

    ret = pthread_create(&tid, nullptr, doTask, &arg);
    ret = pthread_join(tid, nullptr);

    return 0;
}
