/*
EXECUTOR SERVICE & THREAD POOL IMPLEMENTATION
*/


#include <iostream>
#include <chrono>
#include "exer08-exec-service-itask.hpp"
#include "exer08-exec-service-v0a.hpp"
#include "exer08-exec-service-v0b.hpp"
#include "exer08-exec-service-v1a.hpp"
#include "exer08-exec-service-v1b.hpp"
#include "exer08-exec-service-v2a.hpp"
#include "exer08-exec-service-v2b.hpp"



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


    MyExecServiceV0A execService(NUM_THREADS);


    auto lstTask = std::vector<MyTask>(NUM_TASKS);

    for (int i = 0; i < NUM_TASKS; ++i)
        lstTask[i].id = 'A' + i;


    for (auto&& task : lstTask)
        execService.submit(&task);

    std::cout << "All tasks are submitted" << std::endl;


    execService.waitTaskDone();
    std::cout << "All tasks are completed" << std::endl;


    execService.shutdown();


    return 0;
}
