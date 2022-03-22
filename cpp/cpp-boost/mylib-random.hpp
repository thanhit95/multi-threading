/******************************************************
*
* File name:    mylib-random.hpp
*
* Author:       Name:   Thanh Nguyen
*               Email:  thanh.it1995(at)gmail(dot)com
*
* License:      3-Clause BSD License
*
* Description:  The random utility in C++98 Boost
*
******************************************************/



#ifndef _MYLIB_RANDOM_HPP_
#define _MYLIB_RANDOM_HPP_



#include <limits>
#include <boost/random/random_device.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>



namespace mylib {



class RandInt {

private:
    boost::random::random_device rd;
    boost::random::mt19937 mt;
    boost::random::uniform_int_distribution<int> dist;


public:
    RandInt() {
        init(0, std::numeric_limits<int>::max());
    }


    RandInt(int minValue, int maxValueInclusive) {
        init(minValue, maxValueInclusive);
    }


    void init(int minValue, int maxValueInclusive) {
        dist = boost::random::uniform_int_distribution<int>(minValue, maxValueInclusive);
        mt.seed(rd());
    }


    int next() {
        return dist(mt);
    }


private:
    RandInt(const RandInt& other) { }
    void operator=(const RandInt& other) { }


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
