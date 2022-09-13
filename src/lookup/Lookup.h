//
// Created by ms on 2022/9/13.
//

#ifndef LOGEX_LOOKUP_H
#define LOGEX_LOOKUP_H

#include <string>
#include "../message/LogEvent.h"
#include "LookupResult.h"

namespace log4cpp2 {

    class Lookup {
    public:
        virtual std::string lookup(std::string key) {}

        virtual std::string lookup(LogEvent *event, std::string key) {}

        virtual LookupResult evaluate(std::string key) {}

        virtual LookupResult evaluate(LogEvent *event, std::string key) {}
    };

} // log4cpp2

#endif //LOGEX_LOOKUP_H
