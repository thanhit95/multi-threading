/*
INTRODUCTION TO MULTITHREADING
You should try running this app several times and see results.
*/


#include <iostream>
#include <thread>
using namespace std;



void threadFunc() {
    for (int i = 0; i < 300; ++i)
        cout << "B";
}



int main() {
    std::thread th(threadFunc);

    for (int i = 0; i < 300; ++i)
        cout << "A";

    th.join();

    cout << endl;
    return 0;
}
