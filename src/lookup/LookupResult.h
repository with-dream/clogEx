//
// Created by ms on 2022/9/13.
//

#ifndef LOGEX_LOOKUPRESULT_H
#define LOGEX_LOOKUPRESULT_H

#include <string>

namespace log4cpp2 {

    class LookupResult {
    public:
        virtual std::string value() = 0;
    };

} // log4cpp2

#endif //LOGEX_LOOKUPRESULT_H
