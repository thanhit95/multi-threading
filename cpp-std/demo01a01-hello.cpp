/*
HELLO WORLD VERSION MULTITHREADING
Version A01: Using functions
*/


#include <iostream>
#include <thread>
using namespace std;



void doTask() {
    cout << "Hello from example thread" << endl;
}



int main() {
    std::thread th(doTask);

    cout << "Hello from main thread" << endl;

    th.join();
    return 0;
}
