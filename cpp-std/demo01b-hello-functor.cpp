/*
HELLO WORLD VERSION MULTITHREADING
Version B: Using functors
*/


#include <iostream>
#include <string>
#include <thread>
using namespace std;



class Foo {
public:
    void operator()(string message) {
        cout << message << endl;
    }
};



int main() {
    Foo foo;
    std::thread th(foo, "Lorem");

    th.join();
    return 0;
}
