/*
HELLO WORLD VERSION MULTITHREADING
Version A02: Using functions allowing passing 2 arguments
*/


#include <iostream>
#include <thread>
using namespace std;



void routine(char const* message, int number) {
    cout << message << " " << number << endl;
}



int main() {
    std::thread th(routine, "Lorem", 19);
    th.join();
    return 0;
}
