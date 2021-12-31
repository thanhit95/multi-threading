/*
GETTING RETURNED VALUES FROM THREADS
Version A: Using pointers or references (traditional way)
*/


#include <iostream>
#include <thread>
using namespace std;



void doubleValue(int arg, int* res) {
    (*res) = arg * 2;
}



int main() {
    int result[2];

    auto thFoo = std::thread(doubleValue, 5, &result[0]);
    auto thBar = std::thread(doubleValue, 80, &result[1]);

    thFoo.join();
    thBar.join();

    cout << result[0] << endl;
    cout << result[1] << endl;

    return 0;
}
