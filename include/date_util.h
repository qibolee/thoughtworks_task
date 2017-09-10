#ifndef DATE_UTIL_H
#define DATE_UTIL_H

#include <utility>

/**
 * date util for date handle
 */
class date_util {
public:
    // check validity of date, e.g. 2017-09-09(ok), 2017-02-30(not ok)
    static bool check_date(const std::string &date);
    // check validity of during time, e.g. 10:00~12:00(ok), 7:00~10:00(not ok), 10:30~12:30(not ok)
    static bool check_during_time(const std::string &duringTime);
    // convert date string into time number, include beging time and end time, a seconds since the Epoch
    static std::pair<long, long> parse_date_time(const std::string &date, const std::string &duringTime);
    // convert time number into date string, include date and during time
    static std::pair<std::string, std::string> to_date_time(long begTime, long endTime);
};


#endif //DATE_UTIL_H
