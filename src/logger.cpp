#include <logger.hpp>
#include <chrono>
#include <cstdio>
#include <mutex>

static int min_level = logger::ALL;

static std::mutex mtx;

static bool colors = true;

static uint64_t current_time_millis() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()).count();
}

static void get_date_time_str(char *dt_str) {
	char dt_buf[32] = { 0 };
    uint64_t millis = current_time_millis();
    auto t = (std::time_t) (millis / 1000);
	std::strftime(dt_buf, 32, "%Y/%m/%d-%H:%M:%S", std::localtime(&t));
    snprintf(dt_str, 32, "%s.%03d", dt_buf, (int) (millis % 1000));
}

static const char *get_level_str(int level) {
    if (colors) {
        switch (level) {
            case logger::TRACE: {
                return "\033[36mTRACE  \033[39m";
            }
            case logger::DEBUG: {
                return "\033[32mDEBUG  \033[39m";
            }
            case logger::INFO: {
                return "\033[32mINFO   \033[39m";
            }
            case logger::WARNING: {
                return "\033[33mWARNING\033[39m";
            }
            case logger::ERROR: {
                return "\033[31mERROR  \033[39m";
            }
            case logger::FATAL: {
                return "\033[31mFATAL  \033[39m";
            }
            default: {
                return "NONE   ";
            }
        }
    } else {
        switch (level) {
            case logger::TRACE: {
                return "TRACE  ";
            }
            case logger::DEBUG: {
                return "DEBUG  ";
            }
            case logger::INFO: {
                return "INFO   ";
            }
            case logger::WARNING: {
                return "WARNING";
            }
            case logger::ERROR: {
                return "ERROR  ";
            }
            case logger::FATAL: {
                return "FATAL  ";
            }
            default: {
                return "NONE   ";
            }
        }
    }
}

void logger::log(int level, const std::string &msg) {
	if (level < min_level) {
		return;
    }

    char dt_str[32] = { 0 };
    get_date_time_str(dt_str);
    const char *lev_str = get_level_str(level);

    std::lock_guard<std::mutex> lock(mtx); // make logging MT-safe
	printf("%s | %s | %s\n", dt_str, lev_str, msg.c_str());
}

void logger::set_minimum_level(int level) {
    min_level = level;
}

void logger::use_colors(bool val) {
    colors = val;
}
