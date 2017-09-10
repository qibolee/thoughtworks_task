#ifndef BOOKING_MANAGEMENT_H
#define BOOKING_MANAGEMENT_H

#include <vector>
#include <string>
#include <map>
#include <initializer_list>
#include "booking_item.h"

/**
 * booking management for booking, cancel and list income
 */
class booking_management {
public:
    // construct with place list
    booking_management(const std::initializer_list<std::string> &placeList);
    // booking a place
    int booking_place(const std::string &place, const std::string &date, const std::string &duringTime, const std::string &uid);
    // cancel booking
    int cancel_place(const std::string &place, const std::string &date, const std::string &duringTime, const std::string &uid);
    // show income detail
    void list_income() const;

private:
    // calculate price according to during time
    int calc_price(const std::string &date, const std::string &duringTime, bool isBooking) const;
    // do booking place
    int do_booking(std::map<long, booking_item> &placeData, const std::string &date, const std::string &duringTime, const std::string &uid, const std::pair<long, long> &timesPair);
    // do cancel place
    int do_cancel(std::map<long, booking_item> &placeData, std::multimap<long, booking_item> &placeCancelData, const std::string &date, const std::string &duringTime, const std::string &uid, const std::pair<long, long> &timesPair);
    // place name list
    std::vector<std::string> placeName;
    // begin time -> booking_item
    std::vector<std::map<long, booking_item>> bookingData;
    // begin time -> booking_item
    std::vector<std::multimap<long, booking_item>> cancelData;

};



#endif //BOOKING_MANAGEMENT_H
