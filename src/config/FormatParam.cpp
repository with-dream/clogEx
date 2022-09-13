//
// Created by ms on 2022/9/11.
//

#include "FormatParam.h"

namespace log4cpp2 {
    const std::string FormatParam::INHERENT = "_inherent";

    FormatParam::FormatParam() {

    }

    FormatParam::FormatParam(const std::string &inherent, const std::string &category, const std::string &type) : inherent(
            inherent), category(category), type(type) {

    }
} // log4cpp2