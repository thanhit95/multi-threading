#include <iostream>
#include <string>
#include <thread>

using namespace std;



class Foo {
public:
    void operator()(string message) {
        cout << message << endl;
    }
};



int main() {
    Foo foo;

    std::thread th1(foo, "ham");
    std::thread th2(foo, "eggs");

    th1.join();
    th2.join();

    return 0;
}
