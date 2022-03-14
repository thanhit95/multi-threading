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
    void run() {
        boost::thread th(&Example::doTask, "Good day");
        th.join();
    }

private:
    static void doTask(string message) {
        cout << message << endl;
    }
};



int main() {
    Example example;
    example.run();
    return 0;
}
