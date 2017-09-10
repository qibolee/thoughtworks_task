#include <iostream>
#include <utility>
#include <string>
#include "string_util.h"
#include "booking_management.h"
#include "date_util.h"
#include "mlog.h"

int startService();

int main(int argc, const char **argv) {
    startService();
    return 0;
}


// init log util
void init_service() {
    mlog::set_debug_path("./log/debug.log");
    MLOG(MDEBUG, "open debug log");

    mlog::set_trace_path("./log/trace.log");
    MLOG(MTRACE, "open trace log");
    
    mlog::set_warning_path("./log/warning.log");
    MLOG(MWARNING, "open warning log");

    mlog::set_fatal_path("./log/fatal.log");
    MLOG(MFATAL, "open fatal log");
}


// main service
int startService() {
    std::string buf;
    // construct booking management
    booking_management manage({"A", "B", "C", "D"});
    init_service();

    while(std::getline(std::cin, buf)) {
        if (buf.empty()) {
            // show income detail
            manage.list_income();
            continue;
        }
        // split readline into words by ' '
        std::vector<std::string> cmds = string_util::split(buf, ' ');
        int k = 0;
        for (int i = 0; i < cmds.size(); ++i) {
            if (!cmds[i].empty()) {
                if (k != i) {
                    cmds[k] = cmds[i];
                }
                ++k;
            }
        }
        cmds.resize(k);

        if (k == 4) {
            // booking command
            int res = manage.booking_place(cmds[3], cmds[1], cmds[2], cmds[0]);
            if (res == -1) {
                MLOG(MDEBUG, "%s: argv error", buf.c_str());
                std::cout << "Error: the booking is invalid!" << std::endl;
            } else if (res == 1) {
                MLOG(MDEBUG, "%s: argv conflicts", buf.c_str());
                std::cout << "Error: the booking conflicts with existing bookings!" << std::endl;
            } else {
                std::cout << "Success: the booking is accepted!" << std::endl;
            }
        } else if (k == 5) {
            // cancel command
            if (cmds[4] != "C") {
                MLOG(MDEBUG, "%s: argv error", buf.c_str());
                std::cout << "Error: the booking is invalid!" << std::endl;
            } else {
                int res = manage.cancel_place(cmds[3], cmds[1], cmds[2], cmds[0]);
                if (res == -1) {
                    MLOG(MDEBUG, "%s: argv error", buf.c_str());
                    std::cout << "Error: the booking is invalid!" << std::endl;
                } else if (res == 1) {
                    MLOG(MDEBUG, "%s: argv not exist", buf.c_str());
                    std::cout << "Error: the booking being cancelled does not exist!" << std::endl;
                } else {
                    std::cout << "Success: the booking is accepted!" << std::endl;
                }
            }
        } else {
            // error command
            MLOG(MDEBUG, "%s: argv error", buf.c_str());
            std::cout << "Error: the booking is invalid!" << std::endl;
        }
    }

    return 0;
}


