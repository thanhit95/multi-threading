/*
DEADLOCK DEMONSTRATION

There are 2 workers "foo" and "bar".
They try to access resource A and B (following by mutResourceA and mutResourceB).

foo():
    synchronized:
        access resource A

        synchronized:
            access resource B


bar():
    synchronized:
        access resource B

        synchronized:
            access resource A


After first time accessing resource, foo and bar will wait other together ==> Deadlock occurs.
*/


#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std;



std::mutex mutResourceA;
std::mutex mutResourceB;



void foo() {
    mutResourceA.lock();
    cout << "foo enters resource A" << endl;

    std::this_thread::sleep_for(std::chrono::seconds(1));

    mutResourceB.lock();
    cout << "foo enters resource B" << endl;
    mutResourceB.unlock();

    mutResourceA.unlock();
}



void bar() {
    mutResourceB.lock();
    cout << "bar enters resource B" << endl;

    std::this_thread::sleep_for(std::chrono::seconds(1));

    mutResourceA.lock();
    cout << "bar enters resource A" << endl;
    mutResourceA.unlock();

    mutResourceB.unlock();
}



int main() {
    auto thFoo = std::thread(foo);
    auto thBar = std::thread(bar);

    thFoo.join();
    thBar.join();

    cout << "You will never see this statement due to deadlock!" << endl;
    return 0;
}
