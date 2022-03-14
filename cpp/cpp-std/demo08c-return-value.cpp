/*
GETTING RETURNED VALUES FROM THREADS
Version C: Using std::future with the packaged_task
*/


#include <iostream>
#include <string>
#include <utility>
#include <chrono>
#include <thread>
#include <future>
using namespace std;



string doubleValue(int arg) {
    int result = arg * 2;
    std::this_thread::sleep_for(std::chrono::seconds(2));

    cout << "This thread is exiting" << endl;
    return to_string(result);
}



int main() {
    auto ptask = std::packaged_task<string(int)>(doubleValue);
    auto fut = ptask.get_future(); // fut is std::future<string>

    auto th = std::thread(std::move(ptask), 5);

    // Block until ptask finishes
    string result = fut.get();

    cout << result << endl;

    th.join();
    return 0;
}
