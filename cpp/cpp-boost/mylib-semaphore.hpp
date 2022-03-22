/******************************************************
*
* File name:    mylib-semaphore.hpp
*
* Author:       Name:   Thanh Nguyen
*               Email:  thanh.it1995(at)gmail(dot)com
*
* License:      3-Clause BSD License
*
* Description:  The semaphore implementation in C++98 Boost threading
*               This is just a simulation based on the condition variable
*
******************************************************/



#ifndef _MYLIB_SEMAPHORE_HPP_
#define _MYLIB_SEMAPHORE_HPP_



#include <queue>
#include <limits>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>
#include <boost/thread/lock_types.hpp>



namespace mylib
{



class Semaphore {

private:
    typedef boost::unique_lock<boost::mutex> uniquelk;


private:
    volatile int value;
    boost::condition_variable condFreeState;
    boost::mutex mut;

    static int MIN_VALUE;
    static int MAX_VALUE;


public:
    Semaphore(int initialValue) {
        this->value = initialValue;
    }


private:
    Semaphore(const Semaphore& other) { }
    void operator=(const Semaphore& other) { }

#if __cplusplus >= 201103L || (defined(_MSC_VER) && _MSC_VER >= 1900)
    Semaphore(const Semaphore&& other) { }
    void operator=(const Semaphore&& other) { }
#endif


public:
    void acquire() {
        uniquelk lk(mut);

        while (value <= 0) {
            condFreeState.wait(lk);
        }

        if (value > MIN_VALUE) {
            --value;
        }
    }


    void release() {
        uniquelk lk(mut);

        if (value < MAX_VALUE) {
            ++value;
        }

        if (value >= 0) {
            condFreeState.notify_one();
        }
    }


    int getValue() const {
        return value; // does not block
    }

}; // Semaphore



int Semaphore::MIN_VALUE = std::numeric_limits<int>::min();
int Semaphore::MAX_VALUE = std::numeric_limits<int>::max();



} // namespace mylib



#endif // _MYLIB_SEMAPHORE_HPP_
