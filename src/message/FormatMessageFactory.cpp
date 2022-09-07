//
// Created by ms on 2022/9/8.
//

#include "FormatMessageFactory.h"
#include "SampleMessage.h"
#include "../utils/StrUtils.h"

namespace log4cpp2 {
    const char * const FormatMessageFactory::TAG = CLASS_NAME(FormatMessageFactory);

    Message *FormatMessageFactory::newMessage(const std::string &msg) {
        return new SampleMessage(msg);
    }

    Message *FormatMessageFactory::newMessage(const std::string &msg, ...) {
        va_list args;
        va_start(args, msg);
        const std::string res = StrUtils::format(msg.c_str(), args);
        va_end(args);
        return new SampleMessage(res);
    }

    std::string FormatMessageFactory::getTag() {
        return TAG;
    }
}