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

    auto th1 = std::thread(routine, a);
    auto th2 = std::thread(routine, b);

    th1.join();
    th2.join();

    return 0;
}
