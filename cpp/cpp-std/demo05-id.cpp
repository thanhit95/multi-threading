/*
GETTING THREAD'S ID
*/


#include <iostream>
#include <chrono>
#include <thread>
using namespace std;



void doTask() {
    std::this_thread::sleep_for(std::chrono::seconds(2));
    cout << std::this_thread::get_id() << endl;
}



int main() {
    auto thFoo = std::thread(doTask);
    auto thBar = std::thread(doTask);

    cout << "foo's id: " << thFoo.get_id() << endl;
    cout << "bar's id: " << thBar.get_id() << endl;

    thFoo.join();
    thBar.join();

    return 0;
}
