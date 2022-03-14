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



void squareValue(int arg, int& res) {
    res = arg * arg;
}



int main() {
    int result[3];

    auto thFoo = std::thread(doubleValue, 5, &result[0]);
    auto thBar = std::thread(doubleValue, 80, &result[1]);
    auto thEgg = std::thread(squareValue, 7, std::ref(result[2]));

    thFoo.join();
    thBar.join();
    thEgg.join();

    cout << result[0] << endl;
    cout << result[1] << endl;
    cout << result[2] << endl;

    return 0;
}
