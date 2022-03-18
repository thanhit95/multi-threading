/*
SEMAPHORES
Version A: Paper sheets and packages
*/


#include <iostream>
#include <chrono>
#include <thread>
#include <semaphore>
using namespace std;



auto semPackage = std::counting_semaphore(0);
auto semSheet = std::counting_semaphore(2);



void makeOneSheet() {
    for (int i = 0; i < 2; ++i) {
        semSheet.acquire();
        cout << "Make 1 sheet" << endl;
        semPackage.release();
    }
}



void combineOnePackage() {
    for (int i = 0; i < 2; ++i) {
        semPackage.acquire();
        semPackage.acquire();

        cout << "Combine 2 sheets into 1 package" << endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));

        semSheet.release();
        semSheet.release();
    }
}



int main() {
    auto thMakeSheetA = std::thread(&makeOneSheet);
    auto thMakeSheetB = std::thread(&makeOneSheet);
    auto thCombinePackage = std::thread(&combineOnePackage);

    thMakeSheetA.join();
    thMakeSheetB.join();
    thCombinePackage.join();

    return 0;
}
