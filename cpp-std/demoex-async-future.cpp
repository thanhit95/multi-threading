/*
ASYNCHRONOUS PROGRAMMING WITH THE FUTURE
*/


#include <iostream>
#include <thread>
#include <future>


int main() {
    // future from a packaged_task
    std::packaged_task<int()> task([]{ return 7; });    // wrap the function
    std::future<int> fut1 = task.get_future();          // get a future
    std::thread th(std::move(task));                    // launch on a thread


    // future from an async()
    std::future<int> fut2 = std::async(std::launch::async, []{ return 8; });


    // future from a promise
    std::promise<int> prom;
    std::future<int> fut3 = prom.get_future();
    std::thread( [&prom]{ prom.set_value_at_thread_exit(9); }).detach();


    std::cout << "Waiting..." << std::endl;
    fut1.wait();
    fut2.wait();
    fut3.wait();
    th.join();


    std::cout << "Done!" << std::endl;

    std::cout << "Results are: "
              << fut1.get() << ' ' << fut2.get() << ' ' << fut3.get() << std::endl;


    return 0;
}
