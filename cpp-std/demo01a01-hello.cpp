/*
HELLO WORLD VERSION MULTITHREADING
Version A01: Using functions/routines
*/


#include <iostream>
#include <thread>
using namespace std;



void lorem() {
    cout << "Hello from Lorem thread" << endl;
}



int main() {
    std::thread th(lorem);

    cout << "Hello from main thread" << endl;

    th.join();
    return 0;
}
