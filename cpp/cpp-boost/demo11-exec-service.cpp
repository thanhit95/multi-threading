/*
EXECUTOR SERVICES AND THREAD POOLS
*/


#include <iostream>
#include <boost/bind/bind.hpp>
#include <boost/chrono.hpp>
#include <boost/thread.hpp>
#include <boost/asio.hpp>
using namespace std;



void doTask(char name) {
    cout << "Task " << name << " is starting" << endl;
    boost::this_thread::sleep_for(boost::chrono::seconds(3));
    cout << "Task " << name << " is completed" << endl;
}



int main() {
    const int NUM_THREADS = 2;
    const int NUM_TASKS = 5;

    boost::asio::thread_pool pool(NUM_THREADS);

    for (int i = 0; i < NUM_TASKS; ++i) {
        char name = char(i + 'A');
        boost::asio::post(pool, boost::bind(doTask, name));
    }

    pool.join();

    // pool.stop();
    return 0;
}
