#include <iostream>
#include <thread>

using namespace std;



void helloThread() {
    cout << "hello" << endl;
}



int main() {
    std::thread th1(helloThread);
    std::thread th2(helloThread);

    th1.join();
    th2.join();

    return 0;
}
