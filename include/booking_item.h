#ifndef BOOKING_ITEM_H
#define BOOKING_ITEM_H

#include <string>

/**
 * booking item, means a record in booking system
 */
struct booking_item {
    // booking date
    std::string date;
    // booking during time
    std::string duringTime;
    // booking uid
    std::string uid;
    // booking begin date time, seconds since the Epoch
    long begTime;
    // booking end date time, seconds since the Epoch
    long endTime;
};


#endif //BOOKING_ITEM_H

