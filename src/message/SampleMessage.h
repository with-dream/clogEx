//
// Created by ms on 2022/9/8.
//

#ifndef LOGEX_SAMPLEMESSAGE_H
#define LOGEX_SAMPLEMESSAGE_H

#include <string>
#include "Message.h"

namespace log4cpp2 {
    class SampleMessage : public Message {
    public:
        std::string msg;
    public:
        SampleMessage();

        SampleMessage(const std::string msg);
    };
}


#endif //LOGEX_SAMPLEMESSAGE_H
