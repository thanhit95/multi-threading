#ifndef _MYLIB_BLOCKING_QUEUE_HPP_
#define _MYLIB_BLOCKING_QUEUE_HPP_



#include <limits>
#include <queue>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>
#include <boost/thread/lock_types.hpp>
#include <boost/thread/thread.hpp>



namespace mylib
{



template <typename T>
class BlockingQueue {

private:
    typedef boost::unique_lock<boost::mutex> uniquelk;


private:
    boost::condition_variable condEmpty;
    boost::condition_variable condFull;
    boost::mutex mut;

    size_t capacity;
    std::queue<T> q;


public:
    BlockingQueue() : capacity(std::numeric_limits<size_t>::max()) {
    }


    BlockingQueue(size_t capacity) : capacity(capacity) {
    }


private:
    BlockingQueue(const BlockingQueue& other) { }
    void operator=(const BlockingQueue& other) { }

#if __cplusplus >= 201103L || (defined(_MSC_VER) && _MSC_VER >= 1900)
    BlockingQueue(const BlockingQueue&& other) { }
    void operator=(const BlockingQueue&& other) { }
#endif


public:
    bool empty() const {
        return q.empty();
    }


    size_t size() const {
        return q.size();
    }


    // sync enqueue
    void put(const T& value) {
        uniquelk lk(mut);

        while (q.size() >= capacity) {
            condFull.wait(lk);
        }

        q.push(value);
        condEmpty.notify_one();
    }


    // sync dequeue
    T take() {
        uniquelk lk(mut);

        while (q.empty()) {
            condEmpty.wait(lk);
        }

        T result = q.front();
        q.pop();
        condFull.notify_one();

        return result;
    }


    // async enqueue
    void add(const T& value) {
        // Note: For asynchronous operations, we should use a long-live background thread
        // instead of using a temporary thread
        boost::thread(&BlockingQueue<T>::put, this, value).detach();
    }


    // returns false if queue is empty, otherwise returns true and assigns the result
    bool peek(T& result) const {
        uniquelk lk(mut);

        if (q.empty()) {
            return false;
        }

        result = q.front();
        return true;
    }


    void clear() {
        uniquelk lk(mut);

        while (false == q.empty()) {
            q.pop();
        }
    }

}; // BlockingQueue



} // namespace mylib



#endif // _MYLIB_BLOCKING_QUEUE_HPP_
