/*
PASSING ARGUMENTS
Version A: Passing multiple arguments with various data types
*/


#include <iostream>
#include <cstdio>
#include <string>
#include <boost/thread.hpp>
using namespace std;



struct Point {
    int x;
    int y;

    Point(int x, int y): x(x), y(y) { }
};



void doTask(int a, double b, string c, char const* d, Point e) {
    char buffer[50] = { 0 };
    std::sprintf(buffer, "%d  %.1f  %s  %s  (%d %d)", a, b, c.data(), d, e.x, e.y);
    cout << buffer << endl;
}



int main() {
    boost::thread thFoo(doTask, 1, 2, "red", "red", Point(0, 0));
    boost::thread thBar(doTask, 3, 4, "blue", "blue", Point(9, 9));

    thFoo.join();
    thBar.join();

    return 0;
}
