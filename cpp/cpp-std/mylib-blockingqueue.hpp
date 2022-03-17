/******************************************************
*
* File name:    mylib-blockingqueue.hpp
*
* Author:       Name:   Thanh Nguyen
*               Email:  thanh.it1995(at)gmail(dot)com
*
* License:      3-Clause BSD License
*
* Description:  The blocking queue implementation in C++11 std threading
*
******************************************************/



#ifndef _MYLIB_BLOCKING_QUEUE_HPP_
#define _MYLIB_BLOCKING_QUEUE_HPP_



#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>



namespace mylib
{



template <typename T>
class BlockingQueue {

private:
    using uniquelk = std::unique_lock<std::mutex>;


private:
    std::condition_variable condEmpty;
    std::condition_variable condFull;
    std::mutex mut;

    size_t capacity;
    std::queue<T> q;


public:
    BlockingQueue(size_t capacity) : capacity(capacity) {
    }


    BlockingQueue() : BlockingQueue(1) {
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
        uniquelk lk(mut);
        condFull.wait(lk, [&] { return q.size() < capacity; });
        q.push(value);
        condEmpty.notify_one();
    }


    // sync dequeue
    T take() {
        uniquelk lk(mut);
        condEmpty.wait(lk, [&] { return !q.empty(); });
        T result = q.front();
        q.pop();
        condFull.notify_one();
        return result;
    }


    // async enqueue
    void add(const T& value) {
        // Note: For asynchronous operations, we should use a long-live background thread
        // instead of using a temporary thread
        std::thread(&BlockingQueue<T>::put, this, value).detach();
    }


    // returns false if queue is empty, otherwise returns true and assigns the result
    bool peek(T& result) const {
        // uniquelk lk(mut);
        if (q.empty()) {
            return false;
        }

        result = q.front();
        return true;
    }


    void clear() {
        uniquelk lk(mut);
        std::queue<T>().swap(q);
    }

}; // BlockingQueue



} // namespace mylib



#endif // _MYLIB_BLOCKING_QUEUE_HPP_
