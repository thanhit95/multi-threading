/*
EXECUTOR SERVICES AND THREAD POOLS

Executor services in C++ std threading are not supported by default.
So, I use mylib::ExecService for this demonstration.
*/


#include <iostream>
#include "mylib-execservice.hpp"
using namespace std;



void doTask() {
    cout << "Hello the Executor Service" << endl;
}



class MyFunctor {
public:
    void operator()() {
        cout << "Hello Multithreading" << endl;
    }
};



int main() {
    // INIT THE EXECUTOR SERVICE WITH 2 THREADS
    auto execService = mylib::ExecService();
    execService.init(2);


    // SUBMIT
    execService.submit([] { cout << "Hello World" << endl; });

    execService.submit(doTask);

    execService.submit(MyFunctor());


    // WAIT FOR THE COMPLETION OF ALL TASKS AND SHUTDOWN EXECUTOR SERVICE
    execService.waitTaskDone();
    execService.shutdown();

    return 0;
}
