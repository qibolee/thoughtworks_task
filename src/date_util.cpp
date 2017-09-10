#include <time.h>
#include <cstdio>
#include <utility>
#include <string>
#include <cstring>
#include "date_util.h"


// check date string is correct
bool date_util::check_date(const std::string &date) {
    struct tm stm, oldTm;
    std::memset(&stm, 0, sizeof(struct tm));
    char *res = strptime(date.c_str(), "%Y-%m-%d", &stm);
    if (res == NULL || *res != '\0') {
        return false;
    }
    std::memcpy(&oldTm, &stm, sizeof(struct tm));
    // mktime will adjust stm, make it to right status
    mktime(&stm);
    if (stm.tm_year == oldTm.tm_year && stm.tm_mon == oldTm.tm_mon && stm.tm_mday == oldTm.tm_mday) {
        return true;
    }
    return false;
}


// check during time is correct
bool date_util::check_during_time(const std::string &duringTime) {
    int begH = -1, begM = -1, endH = -1, endM = -1;
    int cnt = std::sscanf(duringTime.c_str(), "%d:%d~%d:%d", &begH, &begM, &endH, &endM);
    if (cnt != 4) {
        return false;
    }
    if (begH >=9 && begH < 22 && endH > 9 && endH <= 22 && begM == 0 && endM == 0 && begH < endH) {
        return true;
    }
    return false;
}


// convert date time string into time number, a seconds since the Epoch
std::pair<long, long> date_util::parse_date_time(const std::string &date, const std::string &duringTime) {
    int begH = -1, begM = -1, endH = -1, endM = -1;
    std::sscanf(duringTime.c_str(), "%d:%d~%d:%d", &begH, &begM, &endH, &endM);
    struct tm stm;
    std::memset(&stm, 0, sizeof(struct tm));
    strptime(date.c_str(), "%Y-%m-%d", &stm);
    stm.tm_hour = begH;
    long begTime = (long)mktime(&stm);
    stm.tm_hour = endH;
    long endTime = (long)mktime(&stm);
    return std::make_pair(begTime, endTime);
}

// convert into date time string
std::pair<std::string, std::string> date_util::to_date_time(long begTime, long endTime) {
    struct tm *ptm = localtime((time_t *)&begTime);
    char date[16], duringTime[16];
    strftime(date, 16, "%Y-%m-%d", ptm);
    int begH = ptm->tm_hour;
    ptm = localtime((time_t *)&endTime);
    int endH = ptm->tm_hour;
    std::snprintf(duringTime, 16, "%02d:00~%02d:00", begH, endH);
    return std::make_pair(date, duringTime);
}




