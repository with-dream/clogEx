//
// Created by ms on 2022/9/8.
//

#ifndef LOGEX_FORMATMESSAGEFACTORY_H
#define LOGEX_FORMATMESSAGEFACTORY_H

#include "MessageFactory.h"

namespace log4cpp2 {
    class FormatMessageFactory : public MessageFactory {
    private:
        static const char * const TAG;
    public:
        Message *newMessage(const std::string &msg) override;

        Message *newMessage(const std::string &msg, ...) override;

        std::string getTag() override;
    };
}

#endif //LOGEX_FORMATMESSAGEFACTORY_H
