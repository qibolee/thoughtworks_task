#include <utility>
#include <iostream>
#include <algorithm>
#include "booking_management.h"
#include "date_util.h"
#include "mlog.h"


// construct with place name list
booking_management::booking_management(const std::initializer_list<std::string> &placeList): placeName(placeList), bookingData(placeList.size()), cancelData(placeList.size()) {
    MLOG(MDEBUG, "init booking management");
    for (int i = 0; i < placeName.size(); ++i) {
        MLOG(MDEBUG, "place: %s", placeName[i].c_str());
    }
}


// booking a place
int booking_management::booking_place(const std::string &place, const std::string &date, const std::string &duringTime, const std::string &uid) {
    auto iter = std::find(placeName.begin(), placeName.end(), place);
    // check place is correct
    if (iter == placeName.end()) {
        MLOG(MDEBUG, "%s: place is error", place.c_str());
        // -1 mean argv is not correct
        return -1;
    }
    // check date and during time is correct
    if (!date_util::check_date(date) || !date_util::check_during_time(duringTime)) {
        MLOG(MDEBUG, "%s %s: date or during time is error", date.c_str(), duringTime.c_str());
        // -1 mean argv is not correct
        return -1;
    }

    // do booking
    std::pair<long, long> timesPair = date_util::parse_date_time(date, duringTime);
    std::map<long, booking_item> &placeData = bookingData[iter - placeName.begin()];
    if (placeData.empty()) {
        return do_booking(placeData, date, duringTime, uid, timesPair);
    }
    auto firstIter = placeData.lower_bound(timesPair.first);
    if (firstIter == placeData.end()) {
        // check last record is conflict
        --firstIter;
        if (firstIter->second.endTime > timesPair.first) {
            MLOG(MDEBUG, "%s %s: date time is conflict", date.c_str(), duringTime.c_str());
            // 1 mean booking conflict
            return 1;
        }
    } else if (firstIter == placeData.begin()) {
        // check this record is conflict
        if (firstIter->first < timesPair.second) {
            MLOG(MDEBUG, "%s %s: date time is conflict", date.c_str(), duringTime.c_str());
            // 1 mean booking conflict
            return 1;
        }
    } else {
        // check last and this record is conflict
        if (firstIter->first < timesPair.second) {
            MLOG(MDEBUG, "%s %s: date time is conflict", date.c_str(), duringTime.c_str());
            // 1 mean booking conflict
            return 1;
        }
        --firstIter;
        if (firstIter->second.endTime > timesPair.first) {
            MLOG(MDEBUG, "%s %s: date time is conflict", date.c_str(), duringTime.c_str());
            // 1 mean booking conflict
            return 1;
        }
    }

    return do_booking(placeData, date, duringTime, uid, timesPair);
}


// cancel place
int booking_management::cancel_place(const std::string &place, const std::string &date, const std::string &duringTime, const std::string &uid) {
    auto iter = std::find(placeName.begin(), placeName.end(), place);
    // check place is correct
    if (iter == placeName.end()) {
        MLOG(MDEBUG, "%s: place is error", place.c_str());
        // -1 mean argv is not correct
        return -1;
    }
    // check date and during time is correct
    if (!date_util::check_date(date) || !date_util::check_during_time(duringTime)) {
        MLOG(MDEBUG, "%s %s: date or during time is error", date.c_str(), duringTime.c_str());
        // -1 mean argv is not correct
        return -1;
    }

    std::pair<long, long> timesPair = date_util::parse_date_time(date, duringTime);
    std::map<long, booking_item> &placeData = bookingData[iter - placeName.begin()];
    auto firstIter = placeData.find(timesPair.first);
    // check record of this time, and uid, end time
    if (firstIter == placeData.end() || firstIter->second.uid != uid || firstIter->second.endTime != timesPair.second) {
        MLOG(MDEBUG, "%s %s: date time is error", date.c_str(), duringTime.c_str());
        // 1 mean this record not exist
        return 1;
    }
    std::multimap<long, booking_item> &placeCancelData = cancelData[iter - placeName.begin()];
    
    return do_cancel(placeData, placeCancelData, date, duringTime, uid, timesPair);
}


// list income detail
void booking_management::list_income() const {
    std::cout << "收入汇总" << std::endl;
    std::cout << "---" << std::endl;
    // total income
    int totalIncome = 0;
    // print every place income
    for (int i = 0; i < placeName.size(); ++i) {
        const std::map<long, booking_item> &placeData = bookingData[i];
        const std::multimap<long, booking_item> &placeCancelData = cancelData[i];
        auto iter1 = placeData.begin();
        auto iter2 = placeCancelData.begin();
        int income = 0;
        std::cout << "场地:" << placeName[i] << std::endl;
        while (iter1 != placeData.end() && iter2 != placeCancelData.end()) {
            int price = 0;
            if (iter1->first <= iter2->first) {
                price = calc_price(iter1->second.date, iter1->second.duringTime, true);
                std::cout << iter1->second.date << ' ' << iter1->second.duringTime << ' ' << price << "元" << std::endl;
                ++iter1;
            } else {
                price = calc_price(iter2->second.date, iter2->second.duringTime, false);
                std::cout << iter2->second.date << ' ' << iter2->second.duringTime << " 违约金 " << price << "元" << std::endl;
                ++iter2;
            }
            income += price;
        }
        while (iter1 != placeData.end()) {
            int price = calc_price(iter1->second.date, iter1->second.duringTime, true);
            std::cout << iter1->second.date << ' ' << iter1->second.duringTime << ' ' << price << "元" << std::endl;
            ++iter1;
            income += price;
            
        }
        while (iter2 != placeCancelData.end()) {
            int price = calc_price(iter2->second.date, iter2->second.duringTime, false);
            std::cout << iter2->second.date << ' ' << iter2->second.duringTime << " 违约金 " << price << "元" << std::endl;
            ++iter2;
            income += price;

        }
        std::cout << "小计:" << income << "元" << std::endl;
        if (i + 1 < placeName.size()) {
            std::cout << std::endl;
        }
        totalIncome += income;
    }
    std::cout << "---" << std::endl;
    std::cout << "总计:" << totalIncome << "元" << std::endl;
}


// calculate price according to date and during time
int booking_management::calc_price(const std::string &date, const std::string &duringTime, bool isBooking) const {
    int sumPrice = 0;
    int begH = -1, begM = -1, endH = -1, endM = -1;
    struct tm stm;
    std::memset(&stm, 0, sizeof(struct tm));
    strptime(date.c_str(), "%Y-%m-%d", &stm);
    mktime(&stm);
    std::sscanf(duringTime.c_str(), "%d:%d~%d:%d", &begH, &begM, &endH, &endM);
    MLOG(MDEBUG, "%s %s: calc price", date.c_str(), duringTime.c_str());
    if (stm.tm_wday == 0 || stm.tm_wday == 6) {
        // weekend
        MLOG(MDEBUG, "%s %s: wday=%d weekend", date.c_str(), duringTime.c_str(), stm.tm_wday);
        for (int i = 9; i < 12; ++i) {
            if (i >= begH && i < endH) {
                sumPrice += 40;
                MLOG(MDEBUG, "%s %s: %d +40", date.c_str(), duringTime.c_str(), i);
            }
        }
        for (int i = 12; i < 18; ++i) {
            if (i >= begH && i < endH) {
                MLOG(MDEBUG, "%s %s: %d +50", date.c_str(), duringTime.c_str(), i);
                sumPrice += 50;
            }
        }
        for (int i = 18; i < 22; ++i) {
            if (i >= begH && i < endH) {
                MLOG(MDEBUG, "%s %s: %d +60", date.c_str(), duringTime.c_str(), i);
                sumPrice += 60;
            }
        }
        if (!isBooking) {
            sumPrice /= 4;
        }
    } else {
        // workday
        MLOG(MDEBUG, "%s %s: wday=%d workday", date.c_str(), duringTime.c_str(), stm.tm_wday);
        for (int i = 9; i < 12; ++i) {
            if (i >= begH && i < endH) {
                MLOG(MDEBUG, "%s %s: %d +30", date.c_str(), duringTime.c_str(), i);
                sumPrice += 30;
            }
        }
        for (int i = 12; i < 18; ++i) {
            if (i >= begH && i < endH) {
                MLOG(MDEBUG, "%s %s: %d +50", date.c_str(), duringTime.c_str(), i);
                sumPrice += 50;
            }
        }
        for (int i = 18; i < 20; ++i) {
            if (i >= begH && i < endH) {
                MLOG(MDEBUG, "%s %s: %d +80", date.c_str(), duringTime.c_str(), i);
                sumPrice += 80;
            }
        }
        for (int i = 20; i < 22; ++i) {
            if (i >= begH && i < endH) {
                MLOG(MDEBUG, "%s %s: %d +60", date.c_str(), duringTime.c_str(), i);
                sumPrice += 60;
            }
        }
        if (!isBooking) {
            sumPrice /= 2;
        }
    }
    MLOG(MDEBUG, "%s %s: sumPrice: %d", date.c_str(), duringTime.c_str(), sumPrice);
    return sumPrice; 
}


// do booking
int booking_management::do_booking(std::map<long, booking_item> &placeData, const std::string &date, const std::string &duringTime, const std::string &uid, const std::pair<long, long> &timesPair) {
    booking_item item;
    item.date = date;
    item.duringTime = duringTime;
    item.uid = uid;
    item.begTime = timesPair.first;
    item.endTime = timesPair.second;
    placeData[timesPair.first] = item;
    return 0;
}


// do cancel
int booking_management::do_cancel(std::map<long, booking_item> &placeData, std::multimap<long, booking_item> &placeCancelData, const std::string &date, const std::string &duringTime, const std::string &uid, const std::pair<long, long> &timesPair) {
    booking_item item = placeData[timesPair.first];
    placeData.erase(timesPair.first);
    placeCancelData.insert(std::make_pair(timesPair.first, item));
    return 0;
}



