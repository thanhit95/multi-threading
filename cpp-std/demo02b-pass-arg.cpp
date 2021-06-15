#include <iostream>
#include <string>
#include <thread>

using namespace std;



/*
The arguments to the thread function are moved or copied by value.
If a reference argument needs to be passed to the thread function,
it has to be wrapped (e.g. with std::ref or std::cref).

Passing references to thread functions may cause memory violation (e.g. when object is destroyed).
By wrapping reference arguments with the class template std::reference_wrapper
(using the function templates std::ref and std::cref), you explicitly express your intentions.
*/



void routine(string &msg) {
    cout << msg << endl;
}



int main() {
    string a = "foo";
    string b = "bar";

    // auto th1 = thread(routine, a); // error

    auto th1 = thread(routine, std::ref(a));
    auto th2 = thread(routine, std::ref(b));

    th1.join();
    th2.join();

    return 0;
}
