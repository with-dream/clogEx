//
// Created by ms on 2022/9/13.
//

#ifndef LOGEX_CONTEXTMAPLOOKUP_H
#define LOGEX_CONTEXTMAPLOOKUP_H

#include "Lookup.h"

namespace log4cpp2 {

    class ContextMapLookup : public Lookup {
    private:
    public:
        static const char *TAG;
    };

} // log4cpp2

#endif //LOGEX_CONTEXTMAPLOOKUP_H
