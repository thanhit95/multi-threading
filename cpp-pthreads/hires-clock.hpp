#ifndef _HI_RES_CLOCK_HPP_
#define _HI_RES_CLOCK_HPP_



#include <chrono>



namespace mytool
{



using namespace std::chrono;



class HiResClock {
public:
    static high_resolution_clock::time_point now()
    {
        return high_resolution_clock::now();
    }


    static duration<double>
    getTimeSpan(
        const high_resolution_clock::time_point &t1,
        const high_resolution_clock::time_point &t2)
    {
        auto res = duration_cast<duration<double>>(t2 - t1);
        return res;
    }


    static duration<double>
    getTimeSpan(const high_resolution_clock::time_point &tBefore)
    {
        auto tCurrent = HiResClock::now();
        auto res = HiResClock::getTimeSpan(tBefore, tCurrent);
        return res;
    }
};



} // namespace mytool



#endif // _HI_RES_CLOCK_HPP_
