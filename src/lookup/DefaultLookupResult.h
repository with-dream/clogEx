//
// Created by ms on 2022/9/13.
//

#ifndef LOGEX_DEFAULTLOOKUPRESULT_H
#define LOGEX_DEFAULTLOOKUPRESULT_H

#include "LookupResult.h"

namespace log4cpp2 {

    class DefaultLookupResult : public LookupResult {
    private:
        std::string result;
    public:
        DefaultLookupResult() = default;

        DefaultLookupResult(std::string res);

        std::string value() override;
    };

} // log4cpp2

#endif //LOGEX_DEFAULTLOOKUPRESULT_H
