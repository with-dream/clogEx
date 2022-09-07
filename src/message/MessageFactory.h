//
// Created by ms on 2022/9/5.
//

#ifndef LOGEX_MESSAGEFACTORY_H
#define LOGEX_MESSAGEFACTORY_H

#include <string>
#include "Message.h"

namespace log4cpp2 {

    class MessageFactory {
    public:
        virtual Message *newMessage(const std::string &msg) = 0;
        virtual Message *newMessage(const std::string &msg, ...) = 0;
        virtual std::string getTag() = 0;
    };

} // log4cpp2

#endif //LOGEX_MESSAGEFACTORY_H
