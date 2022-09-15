//
// Created by ms on 2022/9/1.
//

#ifndef LOGEX_PARSE_H
#define LOGEX_PARSE_H

#include "Config.h"
#include "ConfigFactory.h"

namespace log4cpp2 {
    typedef enum _FILE_TYPE {
        XML, JSON
    }FILE_TYPE;

    class Parse {
    protected:
    public:
        static const char *Configuration;
        static const char *Properties;
        static const char *Property;
        static const char *Appenders;
        static const char *Filters;
        static const char *Policies;
        static const char *Loggers;
        static const char *Logger;
        static const char *Root;
        static const char *AppenderRef;
        static const char *TAG;

        static const char *param_ref;
        static const char *param_name;
        static const char *param_status;
        static const char *param_additivity;
        static const char *param_monitorInterval;
        static const char *param_pattern;

    public:
        virtual void parse(const char *path, Param *param) = 0;
    };

} // log4cpp2

#endif //LOGEX_PARSE_H
