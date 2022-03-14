/*
PASSING ARGUMENTS
Version C: Passing normal references
*/


#include <iostream>
#include <string>
#include <boost/ref.hpp>
#include <boost/thread.hpp>
using namespace std;



void doTask(string& msg) {
    cout << msg << endl;
}



int main() {
    string a = "lorem ipsum";
    string b = "dolor amet";

    // We should use boost:ref to pass references
    boost::thread thFoo(doTask, boost::ref(a));
    boost::thread thBar(doTask, boost::ref(b));

    // boost::thread thFoo(doTask, a);
    // boost::thread thBar(doTask, b);

    thFoo.join();
    thBar.join();

    return 0;
}
