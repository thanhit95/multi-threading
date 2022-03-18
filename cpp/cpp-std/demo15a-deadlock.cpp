/*
DEADLOCK
Version A
*/


#include <iostream>
#include <string>
#include <thread>
#include <mutex>
using namespace std;



std::mutex mut;



void doTask(std::string name) {
    mut.lock();

    cout << name << " acquired resource" << endl;

    // mut.unlock(); // Forget this statement ==> deadlock
}



int main() {
    auto thFoo = std::thread(&doTask, "foo");
    auto thBar = std::thread(&doTask, "bar");

    thFoo.join();
    thBar.join();

    cout << "You will never see this statement due to deadlock!" << endl;
    return 0;
}
