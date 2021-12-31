/*
HELLO WORLD VERSION MULTITHREADING
Version B: Using class methods
*/


#include <iostream>
#include <string>
#include <thread>
using namespace std;



class Example {
public:
    void doTask(string message) {
        cout << message << endl;
    }
};



int main() {
    Example example;

    std::thread th(&Example::doTask, &example, "Good day");

    th.join();
    return 0;
}
