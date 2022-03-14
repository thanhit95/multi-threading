/*
HELLO WORLD VERSION MULTITHREADING
Version B: Using functors
*/


#include <iostream>
#include <string>
#include <thread>
using namespace std;



class Example {
public:
    void operator()(string message) {
        cout << message << endl;
    }
};



int main() {
    Example example;

    std::thread th(example, "Good day");

    th.join();
    return 0;
}
