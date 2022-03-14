/*
HELLO WORLD VERSION MULTITHREADING
Version B: Using class methods
*/


#include <iostream>
#include <string>
#include <boost/thread.hpp>
using namespace std;



class Example {
public:
    void doTask(string message) {
        cout << message << endl;
    }
};



int main() {
    Example example;

    boost::thread th(&Example::doTask, &example, "Good day");
    // boost::thread th(boost::bind(&Example::doTask, &example, "Good day"));

    th.join();
    return 0;
}
