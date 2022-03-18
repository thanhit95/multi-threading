/*
SEMAPHORES
Version A: Paper sheets and packages

Semaphores in C++ Boost threading are not supported by default.
So, I use mylib::Semaphore for this demonstration.
*/


#include <iostream>
#include <boost/chrono.hpp>
#include <boost/thread.hpp>
#include "mylib-semaphore.hpp"
using namespace std;



mylib::Semaphore semPackage(0);



void makeOneSheet() {
    for (int i = 0; i < 4; ++i) {
        cout << "Make 1 sheet" << endl;
        boost::this_thread::sleep_for(boost::chrono::seconds(1));
        semPackage.release();
    }
}



void combineOnePackage() {
    for (int i = 0; i < 4; ++i) {
        semPackage.acquire();
        semPackage.acquire();
        cout << "Combine 2 sheets into 1 package" << endl;
    }
}



int main() {
    boost::thread thMakeSheetA(&makeOneSheet);
    boost::thread thMakeSheetB(&makeOneSheet);
    boost::thread thCombinePackage(&combineOnePackage);

    thMakeSheetA.join();
    thMakeSheetB.join();
    thCombinePackage.join();

    return 0;
}
