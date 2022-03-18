/*
PASSING ARGUMENTS
Version B: Passing constant references
*/


#include <iostream>
#include <string>
#include <thread>
using namespace std;



void doTask(const string& msg) {
    cout << msg << endl;
}



int main() {
    auto thFoo = std::thread(&doTask, "foo");
    auto thBar = std::thread(&doTask, "bar");

    thFoo.join();
    thBar.join();

    return 0;
}
