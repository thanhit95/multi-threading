#ifndef _MYTOOL_RANDOM_HPP_
#define _MYTOOL_RANDOM_HPP_



#include <random>
#include <limits>



namespace mytool
{



class RandInt {
private:
    std::random_device rd;
    std::mt19937 mt;
    std::uniform_int_distribution<int> dist;


public:
    RandInt() {
        init(0, 1);
    }


    RandInt(int minValue, int maxValue) {
        init(minValue, maxValue);
    }


    void init(int minValue, int maxValue) {
        dist = std::uniform_int_distribution<int>(minValue, maxValue);
        mt.seed(rd());
    }


    int get() {
        return dist(mt);
    }


    RandInt(const RandInt& other) = default;
    RandInt(RandInt&& other) = default;
    RandInt& operator=(const RandInt& other) = default;
    RandInt& operator=(RandInt&& other) = default;



// STATIC
private:
    static RandInt publicRandInt;

public:
    static int staticGet() {
        return publicRandInt.get();
    }
}; // RandInt



RandInt RandInt::publicRandInt(1, std::numeric_limits<int>::max());



} // namespace mytool



#endif // _MYTOOL_RANDOM_HPP_
