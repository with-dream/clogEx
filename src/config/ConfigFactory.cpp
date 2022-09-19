//
// Created by ms on 2022/9/4.
//

#include "ConfigFactory.h"

#include "../appender/Console.h"
#include "../filter/ThresholdFilter.h"
#include "Parse.h"
#include "../filter/ListWrapFilter.h"
#include "../utils/L.h"
#include "../lookup/ContextMapLookup.h"
#include "../handle/layout/PatternLayout.h"

namespace log4cpp2 {
    void ConfigFactory::createAppenderList(Config *config, std::vector<Param *> &appVector) {
        for (auto &it: appVector) {
            Appender *app = createAppender(it);
            if (!app) {
                //TODO
                continue;
            }
            createAppenderItemList(config, it->child, app);
            config->appender[app->name] = app;
        }
    }

    Appender *ConfigFactory::createAppender(Param *param) {
        Appender *res = nullptr;
        if (StrUtils::icompare(param->tag, Console::TAG)) {
            res = new Console(param->attr);
        }

        return res;
    }

    void
    ConfigFactory::createAppenderItem(Config *config, std::string &tag, std::map<std::string, std::string> &param,
                                      Appender *appender) {
        if (StrUtils::icompare(tag, PatternLayout::TAG)) {
            appender->layout = new PatternLayout(config, param);
        }
    }

    Filter *ConfigFactory::createFilter(Param *param) {
        if (StrUtils::icompare(param->tag, Parse::Filters)) {
            if (!param->child.empty()) {
                auto filterList = new ListWrapFilter();
                for (auto it: param->child) {
                    Filter *filter = createFilter(it);
                    filterList->addFilter(filter);
                }
                return filterList;
            }
            return nullptr;
        } else if (StrUtils::icompare(param->tag, ThresholdFilter::TAG)) {
            return new ThresholdFilter(param->attr);
        }
        return nullptr;
    }

    void ConfigFactory::createAppenderItemList(Config *config, std::vector<Param *> &item, Appender *appender) {
        for (auto &it: item) {
            Filter *filter = createFilter(it);
            if (filter) {
                appender->filters.push_back(filter);
            } else {
                createAppenderItem(config, it->tag, it->attr, appender);
            }
            if (!it->child.empty())
                createAppenderItemList(config, it->child, appender);
        }
    }

    int ConfigFactory::createConfig(Config *config, Param &param) {
        if (!StrUtils::icompare(param.tag, Parse::Configuration)) {
            THROW_ERR("the root tag is not Configuration")
        }

        std::string status = param.attr[Parse::param_status];
        config->status = LevelUtil::getValue(status, ERROR);

        std::string monitorInterval = param.attr[Parse::param_monitorInterval];
        if (!monitorInterval.empty())
            config->monitorInterval = strtoll(monitorInterval.c_str(), nullptr, 10);;

        for (auto &it: param.child) {
            if (StrUtils::icompare(it->tag, Parse::Appenders)) {
                createAppenderList(config, it->child);
            } else if (StrUtils::icompare(it->tag, Parse::Loggers)) {
                createLoggerList(config, it->child);
            } else if (StrUtils::icompare(it->tag, Parse::Properties)) {
                config->property = it->attr;
                for (auto &pit: it->child) {
                    config->property[pit->attr[Parse::param_name]] = pit->text;
                }

                std::map<std::string, FormatParam *> tmpPattern;
                for (auto &it: config->property) {
                    std::set<std::string> set;
                    preProperties(it.first, it.second, config->property, tmpPattern, set);
                }
                for (auto &it: config->property) {
                    L::l("property   " + it.first + "==>" + it.second);
                }
            } else {
                Filter *filter = createFilter(it);
                if (filter) {
                    config->filters.push_back(filter);
                } else {
                    //TODO
                }
            }
        }
        return 0;
    }

    void ConfigFactory::createLoggerList(Config *config, std::vector<Param *> &child) {
        for (auto &it: child) {
            if (StrUtils::icompare(it->tag, Parse::Logger)
                || StrUtils::icompare(it->tag, Parse::Root)) {
                auto logger = createLogger(config, it);
                config->loggerContext[logger->name] = logger;

                if (StrUtils::icompare(it->tag, Parse::Root)) {
                    config->rootLoggerContext = logger;
                }
            } else {
                //TODO
            }
        }
    }

    /**
     * 回溯算法
     * 还有问题 待优化
     * */
    void ConfigFactory::preProperties(std::string key, std::string &value, std::map<std::string, std::string> &property,
                                      std::map<std::string, FormatParam *> &tmpPattern, std::set<std::string> &set) {
        L::l("preProperties==>k:" + key + " v:" + value);
#if 1
        if (set.count(key)) return;
        set.insert(key);

        bool change = false;
        std::smatch match;
        std::string::const_iterator itor = value.cbegin();
        std::vector<std::tuple<std::string, std::string, std::string>> param;
        while (regex_search(itor, value.cend(), match, lookupRx)) {
            itor = match[0].second;
//            L::l("key==>" + match[0].str() + " ss==" + std::to_string(match.size()));
            std::string inherent = match[0].str();
            std::string category = match[1].str();
            std::string type = match[2].str();
            param.emplace_back(inherent, category, type);
        }

        if (param.empty()) return;

        for (auto &it: param) {
            std::string inherent = std::get<0>(it);
            std::string category = std::get<1>(it);
            std::string type = std::get<2>(it);
            std::string res = "";
            std::string keyChild = category + (type.empty() ? "" : (":" + type));
            L::l("search==>" + match[1].str() + "==" + match[2].str());

            if (tmpPattern.count(keyChild) && tmpPattern[keyChild]->isResult) {
                res = tmpPattern[keyChild]->param;
            } else {
                auto param = new FormatParam(inherent, category, type);
                tmpPattern[keyChild] = param;

                if (!type.empty()) {
                    Lookup *lu = getLookup(param->category);
                    if (lu)
                        res = lu->lookup(param->type);
                    if (!res.empty()) {
                        param->param = res;
                        param->isResult = true;
                    }
                }
                if (res.empty() && category != key && property.count(category)) {
                    res = property[category];
                }
            }

            if (!res.empty()) {
                preProperties(keyChild, res, property, tmpPattern, set);
                set.erase(keyChild);

                change = true;
                auto pos = value.find(inherent);
                if (pos != std::string::npos)
                    value = value.replace(pos, inherent.length(), res);
            }
        }

        if (!change) {
            FormatParam *tmp = tmpPattern[key];
            if (!tmp) {
                tmp = new FormatParam(key, key, "");
                tmpPattern[key] = tmp;
            }
            tmp->isResult = true;
            tmp->param = value;
        }
#endif


#if 0
        std::smatch match;
        const std::regex lookupRx(R"(\${1,2}\{([a-zA-Z0-9_]+):?([a-zA-Z0-9_]+)?\})");
        std::string::const_iterator itor = value.cbegin();
        bool change = false;
        while (regex_search(itor, value.cend(), match, lookupRx)) {
            itor = match[0].second;

//            L::l("key==>" + match[0].str() + " ss==" + std::to_string(match.size()));
//            L::l(match[1].str() + "==" + match[2].str());
            std::string inherent = match[0].str();
            std::string category = match[1].str();
            std::string type = match[2].str();
            std::string res = "";

            if (tmpPattern.count(inherent) && tmpPattern[inherent]->isResult) {
                res = tmpPattern[inherent]->param;
            } else {
                auto param = new FormatParam(inherent, category, type);
                tmpPattern[inherent] = param;

                if (!type.empty()) {
                    Lookup *lu = getLookup(param->category);
                    if (lu)
                        res = lu->lookup(param->type);
                    if (!res.empty()) {
                        param->param = res;
                        param->isResult = true;
                    }
                }
                if (res.empty() && property.count(category)) {
                    res = property[category];
                    set.insert(inherent);
                }
            }

            if (!res.empty()) {
                change = true;
                auto pos = value.find(inherent);
                if (pos != std::string::npos)
                    value = value.replace(pos, inherent.length(), res);
            }
        }

        if (change) {
            preProperties(key, value, property, tmpPattern, set);
        }
#endif

#if 0
        std::regex_iterator<std::string::iterator> it(value.begin(), value.end(), lookupRx);
        std::regex_iterator<std::string::iterator> end;
        if (it == end) {
            if (!key.empty()) {
                FormatParam *tmpParam = tmpPattern.count(key) ? tmpPattern[key] : new FormatParam(key, key, "");
                tmpParam->isResult = true;
                tmpParam->param = value;
                tmpPattern[key] = tmpParam;
            }
            return;
        }

        bool retry = false;
        while (it != end) {
            std::string v = it->str();
            v = v.replace(v.begin(), v.begin() + 2, "");
            v = v.replace(v.end() - 1, v.end(), "");
            if (v == key) {
                ++it;
                continue;
            }

            auto r = StrUtils::split(v, ":");
            auto param = new FormatParam(v, r[0], r.size() == 1 ? "" : r[1]);
            tmpPattern[v] = param;

            std::string res = "";
            if (r.size() == 2) {
                if (tmpPattern.count(v) && tmpPattern[v]->isResult) {
                    res = tmpPattern[v]->param;
                } else {
                    Lookup *lu = getLookup(param->category);
                    if (lu)
                        res = lu->lookup(param->type);
                    if (!res.empty()) {
                        param->param = res;
                        param->isResult = true;
                    }
                }
            }
            if (res.empty() && property.count(v)) {
                res = property[v];
                retry = !set.count(v);
            }

            if (!res.empty()) {
                set.insert(v);
                value.replace(value.find(it->str()), it->str().length(), res);
            }

            ++it;
        }
        if (retry)
            preProperties(key, value, property, tmpPattern, set);
#endif
    }

    LoggerContext *ConfigFactory::createLogger(Config *config, Param *param) {
        auto logger = new LoggerContext();
        logger->initParam(config, param->attr);

        for (auto &it: param->child) {
            if (StrUtils::icompare(it->tag, Parse::AppenderRef)) {
                std::string ref = it->attr[Parse::param_ref];
                Appender *appender = config->appender[ref];
                logger->appender.push_back(appender);

                if (!it->child.empty()) {
                    for (auto &filterIt: it->child) {
                        Filter *filter = createFilter(filterIt);
                        if (filter) {
                            appender->refFilters[param->attr[Parse::param_name]] = filter;
                        }
                    }
                }
            } else {
                Filter *filter = createFilter(it);
                if (filter) {
                    logger->filters.push_back(filter);
                }
            }
        }
        return logger;
    }

    ConfigFactory::ConfigFactory() : lookupRx(R"(\${1,2}\{([a-zA-Z0-9_]+):?([a-zA-Z0-9_]+)?\})") {

    }

    Lookup *ConfigFactory::getLookup(const std::string &category) {
        if (lookupMap.count(category)) {
            return lookupMap[category];
        }
        Lookup *lookup = createLookup(category);
        if (lookup) {
            lookupMap[category] = lookup;
        }
        return lookup;
    }

    Lookup *ConfigFactory::createLookup(const std::string &category) {
        Lookup *lookup = nullptr;
        if (StrUtils::icompare(category, ContextMapLookup::TAG)) {
            lookup = new ContextMapLookup();
        }
        return lookup;
    }

} // log4cpp2