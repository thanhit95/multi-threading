/*
ASYNCHRONOUS PROGRAMMING WITH THE FUTURE
*/


#include <iostream>
#include <boost/ref.hpp>
#include <boost/move/move.hpp>
#include <boost/thread.hpp>



int doTaskA() {
    return 7;
}

int doTaskB() {
    return 8;
}

void doTaskC(boost::promise<int> & prom) {
    prom.set_value_at_thread_exit(9);
}



int main() {
    // future from a packaged_task (C++11)
    boost::packaged_task<int> task(doTaskA);                // wrap the function
    boost::unique_future<int> fut1 = task.get_future();     // get a future
    boost::thread th(boost::move(task));                    // launch on a thread


    // future from an async()
    boost::unique_future<int> fut2 = boost::async(boost::launch::async, doTaskB);


    // future from a promise
    boost::promise<int> prom;
    boost::unique_future<int> fut3 = prom.get_future();
    boost::thread(doTaskC, boost::ref(prom)).detach();


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
