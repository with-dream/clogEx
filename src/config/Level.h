//
// Created by ms on 2022/8/31.
//

#ifndef LOGEX_LEVEL_H
#define LOGEX_LEVEL_H

#include <string>
#include <vector>
#include "../utils/StrUtils.h"

namespace log4cpp2 {
    typedef enum {
        UNKNOW_INT = -1,
        OFF_INT = 0,
        FATAL_INT = 100,
        ERROR_INT = 200,
        WARN_INT = 300,
        INFO_INT = 400,
        DEBUG_INT = 500,
        TRACE_INT = 600,
        ALL_INT = 1000,
    } LevelValue;

    typedef struct _Level {
        LevelValue level;
        std::string name;
        std::string sample;

        bool operator==(const struct _Level &l) const {
            return l.level == level && StrUtils::compare(l.name, name) && StrUtils::compare(l.sample, sample);
        }
    } Level;

    const static Level UNKNOW = {UNKNOW_INT, "UNKNOW", "U"};
    const static Level ALL = {ALL_INT, "ALL", "A"};
    const static Level TRACE = {TRACE_INT, "TRACE", "T"};
    const static Level DEBUG = {DEBUG_INT, "DEBUG", "D"};
    const static Level INFO = {INFO_INT, "INFO", "I"};
    const static Level WARN = {WARN_INT, "WARN", "W"};
    const static Level ERROR = {ERROR_INT, "ERROR", "E"};
    const static Level FATAL = {FATAL_INT, "FATAL", "F"};
    const static Level OFF = {OFF_INT, "OFF", "O"};

    const static std::vector<Level> levelList{UNKNOW, ALL, TRACE, DEBUG, INFO, WARN, ERROR, FATAL, OFF};

    class LevelUtil {
    public:
        static Level getValue(const std::string &name) {
            return getValue(name, UNKNOW);
        }

        static Level getValue(const std::string &name, Level def) {
            auto res = std::find_if(levelList.cbegin(), levelList.cend(), [name](const Level &level) {
                return StrUtils::icompare(level.name, name);
            });
            if (res != levelList.cend()) {
                return *res;
            }
            return def;
        }
    };
}
#endif //LOGEX_LEVEL_H
