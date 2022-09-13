//
// Created by ms on 2022/9/6.
//

#ifndef LOGEX_MESSAGE_H
#define LOGEX_MESSAGE_H

#include <string>

namespace log4cpp2 {

    class Message {
    public:
        virtual std::string getMsg();
    };

} // log4cpp2

#endif //LOGEX_MESSAGE_H
