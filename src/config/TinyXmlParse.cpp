//
// Created by ms on 2022/9/1.
//

#include "TinyXmlParse.h"
#include "../utils/Exception.h"
#include "Param.h"
#include <iostream>
#include <list>

namespace log4cpp2 {

    void TinyXmlParse::realParse(tinyxml2::XMLElement *root, Param *res) {
        parseAttr(root, res->attr);
        res->tag = root->Name();

        std::list<std::pair<const tinyxml2::XMLElement *, Param *>> list{std::make_pair(root, res)};
        while(!list.empty()) {
            auto pairNode = list.front();
            list.pop_front();
            const tinyxml2::XMLNode *child = pairNode.first->FirstChild();
            while (child) {
                auto childNode = isElement(child);
                if (!childNode) {
                    child = child->NextSibling();
                    continue;
                }
                auto param = new Param();
                param->tag = childNode->Name();
                parseAttr(childNode, param->attr);
                pairNode.second->child.push_back(param);

                list.emplace_back(childNode, param);
                child = child->NextSibling();
            }
        }
    }

    void TinyXmlParse::parse(const char *path, Param *param) {
        // XML文档
        tinyxml2::XMLDocument document;
        // 加载XML文档
        if (document.LoadFile(path) != tinyxml2::XML_SUCCESS) {
            std::cerr << tinyxml2::XMLDocument::ErrorIDToName(document.ErrorID()) << std::endl;
            return;
        }
        tinyxml2::XMLElement *root = document.FirstChildElement(Configuration);
        if (!root) {
            THROW_ERR("do not find the root tag Configuration")
        }

        realParse(root, param);
        document.Clear();
//        param.print();
    }

    const tinyxml2::XMLElement *TinyXmlParse::isElement(const tinyxml2::XMLNode *node) {
        return dynamic_cast<const tinyxml2::XMLElement *>(node);
    }

    void TinyXmlParse::parseAttr(const tinyxml2::XMLElement *element, std::map<std::string, std::string> &result) {
        auto attr = element->FirstAttribute();
        while (attr) {
            std::string k(attr->Name());
            result[StrUtils::lower(k)] = attr->Value();
            attr = attr->Next();
        }
    }
} // log4cpp2