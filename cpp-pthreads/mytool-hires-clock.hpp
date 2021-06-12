#ifndef _MYTOOL_HIRES_CLOCK_HPP_
#define _MYTOOL_HIRES_CLOCK_HPP_



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
        const high_resolution_clock::time_point &tp1,
        const high_resolution_clock::time_point &tp2)
    {
        auto res = duration_cast<duration<double>>(tp2 - tp1);
        return res;
    }


    static duration<double>
    getTimeSpan(const high_resolution_clock::time_point &tpBefore)
    {
        auto tpCurrent = HiResClock::now();
        auto res = HiResClock::getTimeSpan(tpBefore, tpCurrent);
        return res;
    }
};



} // namespace mytool



#endif // _MYTOOL_HIRES_CLOCK_HPP_
