//
// Created by ms on 2022/9/3.
//

#include "PatternLayout.h"
#include "../utils/StrUtils.h"
#include "../config/Parse.h"

namespace log4cpp2 {
    const char *PatternLayout::TAG = CLASS_NAME(PatternLayout);

    PatternLayout::PatternLayout(Config *config, std::map<std::string, std::string> &param)
            : config(config) {

        if (param.count(Parse::param_pattern)) {
            prepare(param[Parse::param_pattern]);
        }
    }

    char *PatternLayout::toSerializable(LogEvent *event) {

        return nullptr;
    }

    void PatternLayout::prepare(std::string &pattern) {
        std::string tmp;
        int mode;
        for (int i = 0; i < pattern.size(); ++i) {
            switch (pattern[i]) {
                case '%':
                    mode = 1;
                    break;
                case '$':
                    mode = 2;
                    break;
                default:
                    tmp.push_back(pattern[i]);
                    break;
            }

        }
    }
} // log4cpp2