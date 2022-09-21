//
// Created by ms on 2022/9/3.
//

#include "PatternLayout.h"
#include "../../config/Parse.h"
#include "../../utils/L.h"
#include "../../config/RegisterManager.h"

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

    std::string *PatternLayout::toSerializable(LogEvent *event) {
        auto res = new std::string();
        for (auto it: infos) {
            if (it->type == dynamicFI) {
                auto converter = RegisterManager::getConverter(it->key);
                if (converter) {
                    converter->format(event, *res);
                }
            } else if (it->type == constantFI) {
                res->append(it->fullKey);
            } else {
                L::l("type is null key:" + it->fullKey);
            }
        }
        return res;
    }

    void PatternLayout::prepare(std::string &pattern) {
//        L::l("prepare==>" + pattern);
        const std::regex regexParam(R"(%(-?[\d]+)?(\.?(-?[\d]+))?([a-zA-Z]*)(\{(.*?)\})?)");
        std::smatch match;
        std::string::const_iterator itor = pattern.cbegin();
        size_t startIndex = 0, endIndex = 0;
        while (regex_search(itor, pattern.cend(), match, regexParam)) {
            itor = match[0].second;
            std::string fullKey = match[0].str();

            endIndex = pattern.find(fullKey, startIndex);
            int len = endIndex - startIndex;
            if (len > 0) {
                auto constKey = pattern.substr(startIndex, len);
                createConstFI(constKey);
            }

            auto fi = new FormatInfo();
            fi->fullKey = fullKey;
            fi->min = match[1].str();
            fi->max = match[3].str();
            fi->key = match[4].str();
            fi->param = match[6].str();
            fi->type = dynamicFI;
            infos.push_back(fi);

            startIndex = endIndex + fi->fullKey.length();
        }

        if (startIndex < pattern.length() - 1) {
            auto constKey = pattern.substr(startIndex, pattern.length());
            createConstFI(constKey);
        }

//        for (auto it: infos) {
//            it->print();
//        }
    }

    void PatternLayout::createConstFI(const std::string &fk) {
        auto constFi = new FormatInfo();
        constFi->fullKey = fk;
        constFi->type = constantFI;
        infos.push_back(constFi);
    }
} // log4cpp2