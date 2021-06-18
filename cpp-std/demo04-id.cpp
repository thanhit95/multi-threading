#include <iostream>
#include <thread>
#include <chrono>
using namespace std;



void routine() {
    std::this_thread::sleep_for(std::chrono::seconds(2));
    cout << "Thread id is " << std::this_thread::get_id() << endl;
}



int main() {
    auto th1 = std::thread(routine);
    auto th2 = std::thread(routine);

    cout << "th1 id: " << th1.get_id() << endl;
    cout << "th2 id: " << th2.get_id() << endl;

    th1.join();
    th2.join();

    // output: th1 id: thread::id of a non-executing thread
    // cout << "th1 id: " << th1.get_id() << endl;

    return 0;
}
