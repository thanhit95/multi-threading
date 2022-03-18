/*
GETTING RETURNED VALUES FROM THREADS
Using pointers or references (traditional way)
*/


#include <iostream>
#include <boost/ref.hpp>
#include <boost/thread.hpp>
using namespace std;



void doubleValue(int arg, int* res) {
    (*res) = arg * 2;
}



void squareValue(int arg, int& res) {
    res = arg * arg;
}



int main() {
    int result[3];

    boost::thread thFoo(&doubleValue, 5, &result[0]);
    boost::thread thBar(&doubleValue, 80, &result[1]);
    boost::thread thEgg(&squareValue, 7, boost::ref(result[2]));

    thFoo.join();
    thBar.join();
    thEgg.join();

    cout << result[0] << endl;
    cout << result[1] << endl;
    cout << result[2] << endl;

    return 0;
}
