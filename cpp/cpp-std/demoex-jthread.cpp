/*
JTHREAD

std::jthread has the same general behavior as std::thread,
except that jthread automatically rejoins on destruction,
and can be cancelled/stopped in certain situations.
(From https://en.cppreference.com/w/cpp/thread/jthread)
*/


#include <iostream>
#include <thread>
#include <chrono>



void sumIntegers(int a, int b) {
    int t = a + b;
    std::cout << "Sum: " << t << std::endl;
}



void iterateValues(std::stop_token stopTok, int startValue, int endValue) {
    int i = startValue;

    for (; i < endValue; ++i) {
        if (stopTok.stop_requested()) {
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    std::cout << "End of function, i = " << i << std::endl;
}



int main() {
    // DEMO 01: Use std::jthread just like normal std::thread
    std::cout << "DEMO 01:" << std::endl;
    {
        std::jthread thSumInt(&sumIntegers, 100, -30);
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }


    // DEMO 02: Pass the function that takes a std::stop_token as its first argument
    std::cout << "\nDEMO 02:" << std::endl;
    {
        std::jthread thIter(&iterateValues, 0, 1'000'000);

        std::this_thread::sleep_for(std::chrono::seconds(2));
        thIter.request_stop(); // or thIter.get_stop_source().request_stop();

        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "End of program" << std::endl;
    }


    // No need to join thSumInt and thIter, because they auto-join on destruction
    return 0;
}
