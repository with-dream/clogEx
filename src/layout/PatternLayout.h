//
// Created by ms on 2022/9/3.
//

#ifndef LOGEX_PATTERNLAYOUT_H
#define LOGEX_PATTERNLAYOUT_H

#include <map>

#include "Layout.h"
#include "../config/Config.h"
#include "converter/FormatInfo.h"

namespace log4cpp2 {

    class PatternLayout : public Layout {
    public:
        static const char *TAG;
        Config *config;
        std::vector<FormatInfo *> infos;
    private:
        void prepare(std::string &pattern);
    public:
        PatternLayout() {}
        PatternLayout(Config *config, std::map<std::string, std::string> &param);
        char *toSerializable(LogEvent *event) override;
    };

} // log4cpp2

#endif //LOGEX_PATTERNLAYOUT_H
