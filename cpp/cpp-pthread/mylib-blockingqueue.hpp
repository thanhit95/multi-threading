/******************************************************
*
* File name:    mylib-blockingqueue.hpp
*
* Author:       Name:   Thanh Nguyen
*               Email:  thanh.it1995(at)gmail(dot)com
*
* License:      3-Clause BSD License
*
* Description:  The blocking queue implementation in C++11 POSIX threading
*
******************************************************/



#ifndef _MYLIB_BLOCKING_QUEUE_HPP_
#define _MYLIB_BLOCKING_QUEUE_HPP_



#include <limits>
#include <queue>
#include <pthread.h>



namespace mylib
{



template <typename T>
class BlockingQueue {

private:
    pthread_cond_t condEmpty = PTHREAD_COND_INITIALIZER;
    pthread_cond_t condFull = PTHREAD_COND_INITIALIZER;
    pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

    size_t capacity;
    std::queue<T> q;

    struct PendingData {
        BlockingQueue<T> * thisPtr;
        const T data;

        PendingData(BlockingQueue<T> * thisPtr, const T data)
            : thisPtr(thisPtr), data(data) { }
    };


public:
    BlockingQueue() : capacity(std::numeric_limits<size_t>::max()) {
    }


    BlockingQueue(size_t capacity) : capacity(capacity) {
    }


    ~BlockingQueue() {
        pthread_cond_destroy(&condEmpty);
        pthread_cond_destroy(&condFull);
        pthread_mutex_destroy(&mut);
    }


    BlockingQueue(const BlockingQueue& other) = delete;
    BlockingQueue(const BlockingQueue&& other) = delete;
    void operator=(const BlockingQueue& other) = delete;
    void operator=(const BlockingQueue&& other) = delete;


    bool empty() const {
        return q.empty();
    }


    size_t size() const {
        return q.size();
    }


    // sync enqueue
    void put(const T& value) {
        int ret = 0;

        ret = pthread_mutex_lock(&mut);

        while (q.size() >= capacity) {
            ret = pthread_cond_wait(&condFull, &mut);
        }

        q.push(value);

        ret = pthread_mutex_unlock(&mut);
        ret = pthread_cond_signal(&condEmpty);
    }


    // sync dequeue
    T take() {
        T result;
        int ret = 0;

        ret = pthread_mutex_lock(&mut);

        while (q.empty()) {
            // Queue is empty, must wait for 'put'
            ret = pthread_cond_wait(&condEmpty, &mut);
        }

        result = q.front();
        q.pop();

        ret = pthread_mutex_unlock(&mut);
        ret = pthread_cond_signal(&condFull);

        return result;
    }


    // async enqueue
    void add(const T& value) {
        // Note: For asynchronous operations, we should use a long-live background thread
        // instead of using a temporary thread
        pthread_t tid;
        auto arg = new PendingData(this, value);
        pthread_create(&tid, nullptr, &BlockingQueue<T>::putPending, arg);
        pthread_detach(tid);
    }


    // returns false if queue is empty, otherwise returns true and assigns the result
    bool peek(T& result) const {
        if (q.empty()) {
            return false;
        }

        result = q.front();
        return true;
    }


    void clear() {
        int ret;
        ret = pthread_mutex_lock(&mut);
        std::queue<T>().swap(q);
        ret = pthread_mutex_unlock(&mut);
    }


private:
    static void* putPending(void* argVoid) {
        auto arg = (PendingData*) argVoid;
        arg->thisPtr->put(arg->data);
        delete arg;
        arg = nullptr;
        pthread_exit(nullptr);
        return nullptr;
    }

}; // BlockingQueue



} // namespace mylib



#endif // _MYLIB_BLOCKING_QUEUE_HPP_
