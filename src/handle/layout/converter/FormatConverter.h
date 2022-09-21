//
// Created by ms on 2022/9/21.
//

#ifndef LOGEX_FORMATCONVERTER_H
#define LOGEX_FORMATCONVERTER_H

#include <string>
#include "../../../message/LogEvent.h"

namespace log4cpp2 {

    class FormatConverter {
        virtual void format(std::string &buf) {};;
    public:
        virtual void format(LogEvent *event, std::string &buf) {}
    };

} // log4cpp2

#endif //LOGEX_FORMATCONVERTER_H
