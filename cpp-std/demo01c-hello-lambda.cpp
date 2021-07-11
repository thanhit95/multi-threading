/*
HELLO WORLD VERSION MULTITHREADING
Version C: Using lambda
*/


#include <iostream>
#include <string>
#include <thread>
using namespace std;



int main() {
    auto lambda = [](string message) {
        cout << message << endl;
    };

    std::thread th1(lambda, "ham");
    std::thread th2(lambda, "eggs");

    th1.join();
    th2.join();

    return 0;
}
