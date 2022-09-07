//
// Created by ms on 2022/9/1.
//

#ifndef LOGEX_TINYXMLPARSE_H
#define LOGEX_TINYXMLPARSE_H

#include "Parse.h"
#include "../../third_party/tinyxml2/tinyxml2.h"
#include "Param.h"

namespace log4cpp2 {

    class TinyXmlParse : public Parse {
    private:
    private:
        const tinyxml2::XMLElement *isElement(const tinyxml2::XMLNode *node);
        void parseAttr(const tinyxml2::XMLElement *element, std::map<std::string, std::string> &result);
        void realParse(tinyxml2::XMLElement *root, Param *param);
    public:
        TinyXmlParse(){}

        void parse(const char *path, Param *param) override;
    };

} // log4cpp2

#endif //LOGEX_TINYXMLPARSE_H
