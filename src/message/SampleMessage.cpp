//
// Created by ms on 2022/9/8.
//

#include "SampleMessage.h"

namespace log4cpp2 {
    SampleMessage::SampleMessage() {
    }

    SampleMessage::SampleMessage(const std::string msg) {
        this->msg = msg;
    }
}