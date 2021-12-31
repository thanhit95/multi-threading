#ifndef _MYLIB_BLOCKING_QUEUE_HPP_
#define _MYLIB_BLOCKING_QUEUE_HPP_



#include <queue>
#include <mutex>
#include <condition_variable>
#include <stdexcept>



namespace mylib
{



template <typename T>
class BlockingQueue {

    using uniquelk = std::unique_lock<std::mutex>;


private:
    std::condition_variable condEmpty;
    std::condition_variable condFull;
    std::mutex mut;

    size_t capacity;
    std::queue<T> q;


public:
    BlockingQueue(int capacity) {
        if (capacity <= 0)
            throw std::invalid_argument("capacity must be a positive integer");

        this->capacity = capacity;
    }


    BlockingQueue() : BlockingQueue(1) {
    }


    BlockingQueue(const BlockingQueue& other) = delete;
    BlockingQueue(const BlockingQueue&& other) = delete;
    void operator=(const BlockingQueue& other) = delete;
    void operator=(const BlockingQueue&& other) = delete;


    void put(const T& value) {
        uniquelk lk(mut);
        condFull.wait(lk, [&] { return q.size() < capacity; });
        q.push(value);
        condEmpty.notify_one();
    }


    T take() {
        uniquelk lk(mut);
        condEmpty.wait(lk, [&] { return !q.empty(); });
        T result = q.front();
        q.pop();
        condFull.notify_one();
        return result;
    }


    // return false if queue is empty, otherwise return true and assign the result
    bool peek(T& result) const {
        uniquelk lk(mut);

        if (q.empty()) {
            return false;
        }

        result = q.front();
        return true;
    }


    bool empty() const {
        return q.empty();
    }


    size_t size() const {
        return q.size();
    }

};



} // namespace mylib



#endif // _MYLIB_BLOCKING_QUEUE_HPP_
