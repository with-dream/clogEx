//
// Created by ms on 2022/9/13.
//

#include "DefaultLookupResult.h"

#include <utility>

namespace log4cpp2 {
    DefaultLookupResult::DefaultLookupResult(std::string res) : result(std::move(res)) {

    }
    std::string DefaultLookupResult::value() {
        return result;
    }
} // log4cpp2