/*
HELLO WORLD VERSION MULTITHREADING
Version B: Using functors
*/


#include <iostream>
#include <string>
#include <boost/thread.hpp>
using namespace std;



class Example {
public:
    void operator()(string message) {
        cout << message << endl;
    }
};



int main() {
    Example example;

    boost::thread th(example, "Good day");

    th.join();
    return 0;
}
