#ifndef __LOGGER_HPP
#define __LOGGER_HPP

#include <string>
#include <exception>

namespace logger {

// log levels
enum {
	ALL = 0,        // print all messages
    TRACE = 1,      // fine grained details about control flow
    DEBUG = 2,      // debug statements
	INFO = 3,       // general non-critical information
	WARNING = 4,    // something could go wrong
	ERROR = 5,      // something went wrong
    FATAL = 6,      // something went wrong and application cannot recover
	NONE = 7        // do not log at all
};

void log(int level, const std::string &msg);

inline void log(int level, const std::exception &ex) { log(level, ex.what()); }

inline void trace(const std::string &msg) { log(TRACE, msg); }

inline void debug(const std::string &msg) { log(DEBUG, msg); }

inline void info(const std::string &msg) { log(INFO, msg); }

inline void warning(const std::string &msg) { log(WARNING, msg); }

inline void error(const std::string &msg) { log(ERROR, msg); }

inline void fatal(const std::string &msg) { log(FATAL, msg); }

void set_minimum_level(int level);

void use_colors(bool val);

}

#endif // __LOGGER_HPP

