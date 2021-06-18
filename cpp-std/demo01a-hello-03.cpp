#include <iostream>
#include <thread>

using namespace std;



void helloThread(char const* message, int number) {
    cout << message << " " << number << endl;
}



int main() {
    std::thread th1(helloThread, "ham", 19);
    std::thread th2(helloThread, "eggs", 74);

    th1.join();
    th2.join();

    return 0;
}
