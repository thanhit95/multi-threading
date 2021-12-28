/*
HELLO WORLD VERSION MULTITHREADING
Version B: Using class methods
*/


#include <iostream>
#include <string>
#include <thread>
using namespace std;



class Foo {
public:
    void bar(string message) {
        cout << message << endl;
    }
};



int main() {
    Foo foo;
    std::thread th(&Foo::bar, &foo, "Lorem");

    th.join();
    return 0;
}
