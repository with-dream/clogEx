//
// Created by ms on 2022/9/3.
//

#include "PatternLayout.h"
#include "../config/Parse.h"
#include "../utils/L.h"

namespace log4cpp2 {
    const char *PatternLayout::TAG = CLASS_NAME(PatternLayout);

    PatternLayout::PatternLayout(Config *config, std::map<std::string, std::string> &param)
            : config(config) {

        if (param.count(Parse::param_pattern)) {
            std::string v = param[Parse::param_pattern];
            v = v.replace(v.begin(), v.begin() + 2, "");
            v = v.replace(v.end() - 1, v.end(), "");
            prepare(config->property[v]);
        }
    }

    char *PatternLayout::toSerializable(LogEvent *event) {

        return nullptr;
    }

    void PatternLayout::prepare(std::string &pattern) {
//        L::l("prepare==>" + pattern);
        const std::regex regexParam(R"(%(-?[\d]+)?(\.?(-?[\d]+))?([a-zA-Z]*)(\{(.*?)\})?)");
        std::smatch match;
        std::string::const_iterator itor = pattern.cbegin();
        while (regex_search(itor, pattern.cend(), match, regexParam)) {
            itor = match[0].second;

            auto fi = new FormatInfo();
            fi->fullKey = match[0].str();
            fi->min = match[1].str();
            fi->max = match[3].str();
            fi->key = match[4].str();
            fi->param = match[6].str();
            infos.push_back(fi);
        }

//        for (auto it: infos) {
//            it->print();
//        }
    }
} // log4cpp2