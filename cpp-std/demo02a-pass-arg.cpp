#include <iostream>
#include <cstdio>
#include <string>
#include <thread>

using namespace std;



struct Point {
    int x = 0;
    int y = 0;

    Point(int x, int y): x(x), y(y)
    {
    }
};



void routine(int a, double b, string c, char const* d, Point e) {
    char buffer[50] = { 0 };
    std::sprintf(buffer, "%d  %.1f  %s  %s  (%d %d)", a, b, c.data(), d, e.x, e.y);
    cout << buffer << endl;
}



int main() {
    auto th1 = std::thread(routine, 1, 2, "red", "red", Point(0, 0));
    auto th2 = std::thread(routine, 3, 4, "blue", "blue", Point(9, 9));

    th1.join();
    th2.join();

    return 0;
}
