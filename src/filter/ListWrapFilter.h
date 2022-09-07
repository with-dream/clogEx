//
// Created by ms on 2022/9/7.
//

#ifndef LOGEX_LISTWRAPFILTER_H
#define LOGEX_LISTWRAPFILTER_H

#include "Filter.h"

namespace log4cpp2 {
    class ListWrapFilter : public Filter {
    private:
        std::vector<Filter *> filterList;
    public:
        void addFilter(Filter *);
    };
}


#endif //LOGEX_LISTWRAPFILTER_H
