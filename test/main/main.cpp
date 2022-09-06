#include <iostream>
#include <string>
#include "../../src/config/TinyXmlParse.h"
#include "../../src/utils/Exception.h"
#include "../../src/message/MessageFactory.h"
#include "../../src/logger/Logger.h"
#include "../../src/LogManager.h"

using namespace std;

int main() {
//    auto xmlParse = new log4cpp2::XmlParse();
//    xmlParse->parseInit("../log4j2.xml", nullptr);

    map<string, string> m1, m2;
    m1["111"] = "111";
    m1["222"] = "222";
    m1["333"] = "333";

    m2 = m1;
    m1.clear();
    cout << m2["111"] << "==" << StrUtils::toBool("true") << endl;
    return 0;
}
