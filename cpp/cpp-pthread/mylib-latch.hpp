/******************************************************
*
* File name:    mylib-latch.hpp
*
* Author:       Name:   Thanh Nguyen
*               Email:  thanh.it1995(at)gmail(dot)com
*
* License:      3-Clause BSD License
*
* Description:  The count-down latch implementation in C++11 POSIX threading
*
******************************************************/



#ifndef _MYLIB_COUNT_DOWN_LATCH_HPP_
#define _MYLIB_COUNT_DOWN_LATCH_HPP_



#include <pthread.h>



namespace mylib {



class CountDownLatch {

private:
    volatile int count;
    pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t cond = PTHREAD_COND_INITIALIZER;


public:
    CountDownLatch(unsigned int count) {
        this->count = count;
    }


    ~CountDownLatch() {
        int ret;
        ret = pthread_cond_destroy(&cond);
        ret = pthread_mutex_destroy(&mut);
    }


    CountDownLatch(const CountDownLatch& other) = delete;
    CountDownLatch(const CountDownLatch&& other) = delete;
    void operator=(const CountDownLatch& other) = delete;
    void operator=(const CountDownLatch&& other) = delete;


public:
    int getCount() const {
        return count;
    }


    void countDown() {
        pthread_mutex_lock(&mut);

        if (count <= 0) {
            return;
        }

        --count;

        if (count <= 0) {
            pthread_cond_broadcast(&cond);
        }

        pthread_mutex_unlock(&mut);
    }


    void wait() {
        pthread_mutex_lock(&mut);

        while (count > 0) {
            pthread_cond_wait(&cond, &mut);
        }

        pthread_mutex_unlock(&mut);
    }

}; // CountDownLatch



} // namespace mylib



#endif // _MYLIB_COUNT_DOWN_LATCH_HPP_
