/*
HELLO WORLD VERSION MULTITHREADING
Version C: Using lambdas
*/


#include <iostream>
#include <string>
#include <thread>
using namespace std;



int main() {
    auto doTask = [](string message) {
        cout << message << endl;
    };

    std::thread th(doTask, "Good day");

    th.join();
    return 0;
}
