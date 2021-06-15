#include <iostream>
#include <string>
#include <thread>

using namespace std;



int main() {
    auto lambda = [](string message) {
        cout << message << endl;
    };

    thread th1(lambda, "ham");
    thread th2(lambda, "eggs");

    th1.join();
    th2.join();

    return 0;
}
