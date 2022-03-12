/*
EXECUTOR SERVICES AND THREAD POOLS

Executor services in C++ std threading are not supported by default.
So, I use mylib::ExecService for this demonstration.
*/


#include <iostream>
#include <chrono>
#include "mylib-exec-service.hpp"
using namespace std;



int main() {
    constexpr int NUM_THREADS = 2;
    constexpr int NUM_TASKS = 5;

    auto execService = mylib::ExecService();
    execService.init(NUM_THREADS);

    for (int i = 0; i < NUM_TASKS; ++i) {
        execService.submit([=] {
            char id = 'A' + i;
            std::cout << "Task " << id << " is starting" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(3));
            std::cout << "Task " << id << " is completed" << std::endl;
        });
    }

    std::cout << "All tasks are submitted" << std::endl;

    execService.waitTaskDone();
    std::cout << "All tasks are completed" << std::endl;

    execService.shutdown();

    return 0;
}
