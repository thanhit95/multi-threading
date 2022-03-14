/*
EXECUTOR SERVICE & THREAD POOL IMPLEMENTATION
*/


#include <iostream>
#include <boost/chrono.hpp>
#include <boost/thread.hpp>
#include "exer07-exec-service-itask.hpp"
#include "exer07-exec-service-v1a.hpp"
#include "exer07-exec-service-v1b.hpp"
#include "exer07-exec-service-v2a.hpp"
#include "exer07-exec-service-v2b.hpp"



class MyTask : public ITask {
public:
    char id;

public:
    void run() {
        std::cout << "Task " << id << " is starting" << std::endl;
        boost::this_thread::sleep_for(boost::chrono::seconds(3));
        std::cout << "Task " << id << " is completed" << std::endl;
    }
};



int main() {
    const int NUM_THREADS = 2;
    const int NUM_TASKS = 5;


    MyExecServiceV1A execService(NUM_THREADS);


    std::vector<MyTask> lstTask(NUM_TASKS);

    for (int i = 0; i < NUM_TASKS; ++i)
        lstTask[i].id = 'A' + i;


    for (int i = 0; i < NUM_TASKS; ++i) {
        execService.submit(&lstTask[i]);
    }

    std::cout << "All tasks are submitted" << std::endl;


    execService.waitTaskDone();
    std::cout << "All tasks are completed" << std::endl;


    execService.shutdown();


    return 0;
}
