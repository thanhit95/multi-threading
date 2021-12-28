/*
THREAD JOINS
*/


#include <iostream>
#include <thread>
using namespace std;



void threadFunc() {
    // Doing a heavy task...
    for (int i = 0; i < 1000000000; ++i);

    cout << "First" << endl;
}



int main() {
    std::thread th(threadFunc);

    th.join();

    cout << "Second" << endl;

    return 0;
}
