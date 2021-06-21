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
