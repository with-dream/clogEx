//
// Created by ms on 2022/9/3.
//

#include "PatternLayout.h"
#include "../utils/StrUtils.h"

namespace log4cpp2 {
    const char *PatternLayout::TAG = CLASS_NAME(PatternLayout);

    PatternLayout::PatternLayout(Config *config, std::map<std::string, std::string> &param)
            : config(config) {

    }
} // log4cpp2