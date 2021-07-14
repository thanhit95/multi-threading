/*
THREAD POOL & EXECUTOR SERVICE IMPLEMENTATION
*/


#include <iostream>
#include <chrono>
// #include "ex07-thread-pool-v1.hpp"
// #include "ex07-thread-pool-v2a.hpp"
#include "ex07-thread-pool-v2b.hpp"



class MyTask : public ITask {
public:
    char id;

public:
    void run() override {
        std::cout << "Task " << id << " is starting" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(3));
        std::cout << "Task " << id << " is completed" << std::endl;
    }
};



int main() {
    constexpr int NUM_THREADS = 2;
    constexpr int NUM_TASKS = 5;


    ThreadPoolV2B threadPool;
    threadPool.init(NUM_THREADS);


    std::vector<MyTask> lstTasks(NUM_TASKS);

    for (int i = 0; i < NUM_TASKS; ++i)
        lstTasks[i].id = 'A' + i;


    for (auto&& task : lstTasks)
        threadPool.submit(&task);

    std::cout << "All tasks are submitted" << std::endl;


    threadPool.waitTaskDone();
    std::cout << "All tasks are completed" << std::endl;


    threadPool.shutdown();


    return 0;
}
