/*
SEMAPHORE

In an exam, each candidate is given a couple of 2 scratch papers.
Write a program to illustrate this scene.
The program will combine 2 scratch papers into one test package, concurrenly.

The problem in version 01 is:
    When "makeOnePaper" produces too fast, there are a lot of pending papers...

This version 02 solves the problem:
    Use a semaphore to restrict "makeOnePaper". Only make papers when a package is finished.
*/


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



auto semPackage = std::counting_semaphore(0);
auto semPaper = std::counting_semaphore(2);



void makeOnePaper() {
    for (int i = 0; i < 4; ++i) {
        semPaper.acquire();

        cout << "Make 1 paper" << endl;

        semPackage.release();
    }
}



void combineOnePackage() {
    for (int i = 0; i < 4; ++i) {
        semPackage.acquire();
        semPackage.acquire();

        cout << "Combine 2 papers into 1 package" << endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));

        semPaper.release();
        // missing one statement: semPaper.release() ==> DEADLOCK
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
