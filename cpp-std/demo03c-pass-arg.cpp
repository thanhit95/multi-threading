/*
PASSING ARGUMENTS
Version C: Passing normal references
*/


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



void doTask(string& msg) {
    cout << msg << endl;
}



int main() {
    string a = "lorem ipsum";
    string b = "dolor amet";

    // auto thFoo = std::thread(doTask, a); // error

    auto thFoo = std::thread(doTask, std::ref(a));
    auto thBar = std::thread(doTask, std::ref(b));

    thFoo.join();
    thBar.join();

    return 0;
}
