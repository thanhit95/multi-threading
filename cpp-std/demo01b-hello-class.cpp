#include <iostream>
#include <string>
#include <thread>

using namespace std;



class Foo {
public:
    void bar(string message) {
        cout << message << endl;
    }
};



int main() {
    Foo foo;

    std::thread th1(&Foo::bar, &foo, "ham");
    std::thread th2(&Foo::bar, &foo, "eggs");

    th1.join();
    th2.join();

    return 0;
}
