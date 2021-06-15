#ifndef _MYTOOL_RANDOM_HPP_
#define _MYTOOL_RANDOM_HPP_



#include <random>



namespace mytool
{



class RandIntGenerator {
private:
    std::random_device rd;
    std::mt19937 mt;
    std::uniform_int_distribution<int> dist;


public:
    RandIntGenerator() {
        init(0, 1);
    }


    RandIntGenerator(int minValue, int maxValue) {
        init(minValue, maxValue);
    }


    void init(int minValue, int maxValue) {
        dist = std::uniform_int_distribution<int>(minValue, maxValue);
        mt.seed(rd());
    }


    int get() {
        return dist(mt);
    }
}; // RandIntGenerator



} // namespace mytool



#endif // _MYTOOL_RANDOM_HPP_
