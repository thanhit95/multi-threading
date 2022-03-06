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
    void run() {
        std::thread th(&Example::doTask, "Good day");
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
