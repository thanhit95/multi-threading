/******************************************************
*
* File name:    mylib-random.hpp
*
* Author:       Name:   Thanh Nguyen
*               Email:  thanh.it1995(at)gmail(dot)com
*
* License:      3-Clause BSD License
*
* Description:  The random utility in C++11 std
*
******************************************************/



#ifndef _MYLIB_RANDOM_HPP_
#define _MYLIB_RANDOM_HPP_



#include <random>
#include <limits>



namespace mylib {



class RandInt {

private:
    std::random_device rd;
    std::mt19937 mt;
    std::uniform_int_distribution<int> dist;


public:
    RandInt() {
        init(0, std::numeric_limits<int>::max());
    }


    RandInt(int minValue, int maxValueInclusive) {
        init(minValue, maxValueInclusive);
    }


    void init(int minValue, int maxValueInclusive) {
        dist = std::uniform_int_distribution<int>(minValue, maxValueInclusive);
        mt.seed(rd());
    }


    int next() {
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
    static int get(int maxExclusive) {
        return publicRandInt.next() % maxExclusive;
    }

}; // RandInt



RandInt RandInt::publicRandInt;



} // namespace mylib



#endif // _MYLIB_RANDOM_HPP_
