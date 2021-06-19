/*
SEMAPHORE

In an exam, each candidate is given a couple of 2 scratch papers.
Write a program to illustrate this scene.
The program will combine 2 scratch papers into one test package, concurrenly.
*/


#include <iostream>
#include <thread>
#include <semaphore>
#include <chrono>
using namespace std;



auto semPackage = std::counting_semaphore(0);   // max value is 16, current value is 0



void makeOnePaper() {
    for (int i = 0; i < 4; ++i) {
        cout << "Make 1 paper" << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));

        semPackage.release();
    }
}



void combineOnePackage() {
    for (int i = 0; i < 4; ++i) {
        semPackage.acquire();
        semPackage.acquire();
        cout << "Combine 2 papers into 1 package" << endl;
    }
}



int main() {
    auto thMakePaperA = std::thread(makeOnePaper);
    auto thMakePaperB = std::thread(makeOnePaper);
    auto thCombinePackage = std::thread(combineOnePackage);

    thMakePaperA.join();
    thMakePaperB.join();
    thCombinePackage.join();

    return 0;
}
