/*
GETTING RETURNED VALUES FROM THREADS
Version B: Using std::future with the promise
*/


#include <iostream>
#include <chrono>
#include <thread>
#include <future>
using namespace std;



void doubleValue(int arg, std::promise<int> & prom) {
    int result = arg * 2;
    std::this_thread::sleep_for(std::chrono::seconds(2));

    prom.set_value(result);

    std::this_thread::sleep_for(std::chrono::seconds(2));
    cout << "This thread is exiting" << endl;
}



int main() {
    auto prom = std::promise<int>();
    auto fut = prom.get_future(); // fut is std::future<int>

    auto th = std::thread(&doubleValue, 5, std::ref(prom));

    // Block until prom.set_value() executes
    int result = fut.get();

    cout << result << endl;

    th.join();
    return 0;
}
