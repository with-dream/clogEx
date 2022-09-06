//
// Created by ms on 2022/9/3.
//

#ifndef LOGEX_THRESHOLDFILTER_H
#define LOGEX_THRESHOLDFILTER_H

#include <map>

#include "Filter.h"

namespace log4cpp2 {

    class ThresholdFilter : public Filter {
    public:
        static const char *TAG;
    public:
        ThresholdFilter() {}

        ThresholdFilter(std::map<std::string, std::string> param);
    };

} // log4cpp2

#endif //LOGEX_THRESHOLDFILTER_H
