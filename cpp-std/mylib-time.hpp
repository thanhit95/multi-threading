#ifndef _MYLIB_TIME_HPP_
#define _MYLIB_TIME_HPP_



#include <ctime>
#include <chrono>



namespace mylib {



namespace chro = std::chrono;
using sysclock = chro::system_clock;



class HiResClock {
    using stdhrc = chro::high_resolution_clock;

public:
    static inline stdhrc::time_point now()
    {
        return stdhrc::now();
    }


    template< typename duType=chro::duration<double> >
    static inline
    duType
    getTimeSpan(
        const stdhrc::time_point& tp1,
        const stdhrc::time_point& tp2)
    {
        auto res = chro::duration_cast<duType>(tp2 - tp1);
        return res;
    }


    template< typename duType=chro::duration<double> >
    static inline
    duType
    getTimeSpan(const stdhrc::time_point& tpBefore)
    {
        auto tpCurrent = HiResClock::now();
        auto res = HiResClock::getTimeSpan<duType>(tpBefore, tpCurrent);
        return res;
    }
};



char* getTimePointStr(const sysclock::time_point& tp) {
    std::time_t timeStamp = sysclock::to_time_t(tp);
    return std::ctime(&timeStamp);
}



template<class clock = sysclock>
class clock::time_point getTimePoint(
    int year, int month, int day,
    int hour, int minute, int second)
{
    std::tm t{};
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
template<class clock = sysclock>
chro::time_point<clock>
getTimePointFutureFloor(const chro::time_point<clock>& tp, int numSeconds) {
    // auto tpFuture = tp + chro::seconds(2 * numSeconds);
    // auto durationFuture = tpFuture.time_since_epoch();

    // durationFuture = durationFuture - (durationFuture % numSeconds);

    // tpFuture = chro::time_point<clock>(durationFuture);
    // return tpFuture;

    auto duSeconds = chro::seconds(numSeconds);

    auto durationFromTp = chro::time_point_cast<chro::seconds>(tp).time_since_epoch();

    auto durationFuture = durationFromTp + (duSeconds * 2);
    durationFuture = durationFuture - (durationFuture % duSeconds);

    auto tpFuture = chro::time_point<clock>(durationFuture);
    return tpFuture;
}



} // namespace mylib



#endif // _MYLIB_TIME_HPP_
