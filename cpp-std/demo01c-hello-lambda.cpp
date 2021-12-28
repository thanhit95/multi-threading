/*
HELLO WORLD VERSION MULTITHREADING
Version C: Using lambdas
*/


#include <iostream>
#include <string>
#include <thread>
using namespace std;



int main() {
    auto lambda = [](string message) {
        cout << message << endl;
    };

    std::thread th(lambda, "Lorem");

    th.join();
    return 0;
}
