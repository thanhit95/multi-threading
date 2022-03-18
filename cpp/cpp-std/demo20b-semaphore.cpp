/*
SEMAPHORES
Version B: Tires and chassis
*/


#include <iostream>
#include <chrono>
#include <thread>
#include <semaphore>
using namespace std;



auto semTire = std::counting_semaphore(4);
auto semChassis = std::counting_semaphore(0);



void makeTire() {
    for (int i = 0; i < 8; ++i) {
        semTire.acquire();

        cout << "Make 1 tire" << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));

        semChassis.release();
    }
}



void makeChassis() {
    for (int i = 0; i < 4; ++i) {
        semChassis.acquire();
        semChassis.acquire();
        semChassis.acquire();
        semChassis.acquire();

        cout << "Make 1 chassis" << endl;
        std::this_thread::sleep_for(std::chrono::seconds(3));

        semTire.release();
        semTire.release();
        semTire.release();
        semTire.release();
    }
}



int main() {
    auto thTireA = std::thread(&makeTire);
    auto thTireB = std::thread(&makeTire);
    auto thChassis = std::thread(&makeChassis);

    thTireA.join();
    thTireB.join();
    thChassis.join();

    return 0;
}
