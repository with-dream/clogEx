//
// Created by ms on 2022/9/21.
//

#include "RegisterManager.h"
#include "../handle/layout/converter/MessagePatternConverter.h"

namespace log4cpp2 {
    FormatConverter *RegisterManager::getConverter(std::string &key) {
        if (StrUtils::compare("m", key) || StrUtils::compare("msg", key) || StrUtils::compare("message", key)) {
            return new MessagePatternConverter();
        }
        return nullptr;
    }
} // log4cpp2