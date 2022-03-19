/*
EXECUTOR SERVICES AND THREAD POOLS
*/


#include <iostream>
#include <boost/bind/bind.hpp>
#include <boost/thread.hpp>
#include <boost/asio.hpp>
using namespace std;



void doTask() {
    cout << "Hello the Executor Service" << endl;
}



class MyFunctor {
public:
    void operator()() {
        cout << "Hello Multithreading" << endl;
    }
};



int main() {
    // INIT THE EXECUTOR SERVICE WITH 2 THREADS
    boost::asio::thread_pool pool(2);


    // SUBMIT
    boost::asio::post(pool, boost::bind(&doTask /* , argument1, argument2,... */));
    boost::asio::post(pool, MyFunctor());


    // WAIT FOR THE COMPLETION OF ALL TASKS AND SHUTDOWN EXECUTOR SERVICE
    pool.join();
    pool.stop();

    return 0;
}
