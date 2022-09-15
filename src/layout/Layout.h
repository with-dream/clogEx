//
// Created by ms on 2022/9/1.
//

#ifndef LOGEX_LAYOUT_H
#define LOGEX_LAYOUT_H

#include <string>
#include "../message/LogEvent.h"

namespace log4cpp2 {

    class Layout {
    public:
        virtual char *toSerializable(LogEvent *event) = 0;
    };

} // log4cpp2

#endif //LOGEX_LAYOUT_H
