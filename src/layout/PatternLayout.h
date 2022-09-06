//
// Created by ms on 2022/9/3.
//

#ifndef LOGEX_PATTERNLAYOUT_H
#define LOGEX_PATTERNLAYOUT_H

#include <map>

#include "Layout.h"

namespace log4cpp2 {

    class PatternLayout : public Layout{
    public:
        static const char *TAG;
    public:
        PatternLayout(){}
        PatternLayout(std::map<std::string, std::string> &param);
    };

} // log4cpp2

#endif //LOGEX_PATTERNLAYOUT_H
