#ifndef MLOG_H
#define MLOG_H

#include <mutex>
#include <memory>
#include <ctime>
#include <cstdarg>
#include <iomanip>


enum {
    MDEBUG,
    MTRACE,
    MWARNING,
    MFATAL
};


#define MLOG(level, format, ...) mlog::log(level, __func__, __FILE__, __LINE__, format"\n", ##__VA_ARGS__)


/**
 * a log util for debug
 * this log including four levels(debug, trace, warning and fatal)
 */
class mlog {
public:
    // the total control
    static void log(int level, const char *func, const char *file, int line, const char *fmt, ...);

    // set path file of debug log
    static void set_debug_path(const char *path);
    // set path file of trace log
    static void set_trace_path(const char *path);
    // set path file of warning log
    static void set_warning_path(const char *path);
    // set path file of fatal log
    static void set_fatal_path(const char *path);

private:
    // debug log function
    static void debug(const char *func, const char *file, int line, const char *fmt, va_list args);
    // trace log function
    static void trace(const char *func, const char *file, int line, const char *fmt, va_list args);
    // warning log function
    static void warning(const char *func, const char *file, int line, const char *fmt, va_list args);
    // fatal log function
    static void fatal(const char *func, const char *file, int line, const char *fmt, va_list args);
    // get now time save into buf
    static std::size_t get_time(char *buf, std::size_t len);

    // file descriptor for every log path
    static int debug_fd;
    static int trace_fd;
    static int warning_fd;
    static int fatal_fd;
    // buf size
    static std::size_t buf_size;
    // buf for every log
    static std::shared_ptr<char> debug_buf;
    static std::shared_ptr<char> trace_buf;
    static std::shared_ptr<char> warning_buf;
    static std::shared_ptr<char> fatal_buf;
    // time buf size
    static std::size_t tm_size;
    // time buf for every log
    static std::shared_ptr<char> debug_tm;
    static std::shared_ptr<char> trace_tm;
    static std::shared_ptr<char> warning_tm;
    static std::shared_ptr<char> fatal_tm;
    // mutex for every log
    static std::mutex debug_mtx;
    static std::mutex trace_mtx;
    static std::mutex warning_mtx;
    static std::mutex fatal_mtx;
};



#endif //MLOG_H




