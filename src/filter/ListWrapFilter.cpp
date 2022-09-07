//
// Created by ms on 2022/9/7.
//

#include "ListWrapFilter.h"

namespace log4cpp2 {
    void ListWrapFilter::addFilter(log4cpp2::Filter *filter) {
        if (filter) {
            this->filterList.push_back(filter);
        } else {
            std::cout << "ListWrapFilter addFilter null" << std::endl;
        }
    }
}