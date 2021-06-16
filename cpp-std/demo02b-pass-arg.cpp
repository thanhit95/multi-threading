#include <iostream>
#include <string>
#include <thread>

using namespace std;



void routine(const string &msg) {
    cout << msg << endl;
}



int main() {
    string a = "foo";
    string b = "bar";

    auto th1 = thread(routine, a);
    auto th2 = thread(routine, b);

    th1.join();
    th2.join();

    return 0;
}
