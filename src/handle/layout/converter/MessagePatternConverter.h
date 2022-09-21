//
// Created by ms on 2022/9/21.
//

#ifndef LOGEX_MESSAGEPATTERNCONVERTER_H
#define LOGEX_MESSAGEPATTERNCONVERTER_H

#include "FormatConverter.h"

namespace log4cpp2 {

    class MessagePatternConverter : public FormatConverter {
        void format(LogEvent *event, std::string &buf) override;
    };

} // log4cpp2

#endif //LOGEX_MESSAGEPATTERNCONVERTER_H
