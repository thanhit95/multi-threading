/******************************************************
*
* File name:    mylib-time.hpp
*
* Author:       Name:   Thanh Nguyen
*               Email:  thanh.it1995(at)gmail(dot)com
*
* License:      3-Clause BSD License
*
* Description:  The time utility in C++98 Boost
*
******************************************************/



#ifndef _MYLIB_TIME_HPP_
#define _MYLIB_TIME_HPP_



#include <ctime>
#include <boost/chrono.hpp>



namespace mylib
{



namespace chro = boost::chrono;
typedef chro::system_clock sysclock;



class HiResClock {

private:
    typedef chro::high_resolution_clock stdhrc;


public:
    static inline stdhrc::time_point now()
    {
        return stdhrc::now();
    }


    template< typename duType >
    static inline
    duType
    getTimeSpan(
        const stdhrc::time_point& tp1,
        const stdhrc::time_point& tp2)
    {
        duType res = chro::duration_cast<duType>(tp2 - tp1);
        return res;
    }


    template< typename duType >
    static inline
    duType
    getTimeSpan(const stdhrc::time_point& tpBefore)
    {
        stdhrc::time_point tpCurrent = HiResClock::now();
        duType res = HiResClock::getTimeSpan<duType>(tpBefore, tpCurrent);
        return res;
    }

}; // HiResClock



char* getTimePointStr(const sysclock::time_point& tp) {
    std::time_t timeStamp = sysclock::to_time_t(tp);
    return std::ctime(&timeStamp);
}



template<class clock>
class clock::time_point getTimePoint(
    int year, int month, int day,
    int hour, int minute, int second)
{
    std::tm t;
    t.tm_year = year - 1900;
    t.tm_mon = month - 1;
    t.tm_mday = day;
    t.tm_hour = hour;
    t.tm_min = minute;
    t.tm_sec = second;
    return clock::from_time_t(std::mktime(&t));
}



// tp += numSeconds * 2;
// tp -= (x % numSeconds)
template<class clock, typename duType>
chro::time_point<clock>
getTimePointFutureFloor(const chro::time_point<clock>& tp, int numSeconds) {
    chro::seconds duSeconds(numSeconds);

    chro::duration<duType> durationFromTp = chro::time_point_cast<chro::seconds>(tp).time_since_epoch();

    chro::duration<duType> durationFuture = durationFromTp + (duSeconds * 2);
    durationFuture = durationFuture - (durationFuture % duSeconds);

    chro::time_point<clock> tpFuture(durationFuture);
    return tpFuture;
}



} // namespace mylib



#endif // _MYLIB_TIME_HPP_
