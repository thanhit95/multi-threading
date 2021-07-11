/*
HELLO WORLD VERSION MULTITHREADING
Version A02: Using functions with passing an argument
*/


#include <iostream>
#include <thread>
using namespace std;



void helloThread(int value) {
    cout << value << endl;
}



int main() {
    std::thread th1(helloThread, 1);
    std::thread th2(helloThread, 2);

    th1.join();
    th2.join();

    return 0;
}
