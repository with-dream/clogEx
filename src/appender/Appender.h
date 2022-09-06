//
// Created by ms on 2022/8/31.
//

#ifndef LOGEX_APPENDER_H
#define LOGEX_APPENDER_H


#include <string>
#include <vector>
#include <map>
#include "../filter/Filter.h"
#include "../layout/Layout.h"
#include "../policy/Policy.h"

namespace log4cpp2 {
    class Appender {
    public:
        std::string name;
        std::vector<Filter *> filters;
        Layout *layout;
        std::vector<Policy *> policies;
    public:

    };
}

#endif //LOGEX_APPENDER_H
