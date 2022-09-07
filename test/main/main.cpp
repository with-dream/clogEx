#include <iostream>
#include <string>
#include "../../src/config/TinyXmlParse.h"
#include "../../src/utils/Exception.h"
#include "../../src/message/MessageFactory.h"
#include "../../src/logger/Logger.h"
#include "../../src/LogManager.h"

using namespace std;

#include <map>
#include <memory>

//https://github.com/rttrorg/rttr
int main() {
    auto manager = new log4cpp2::LogManager();
    int ret = manager->init("../log4j2.xml");
    cout << "init ret==>" << ret << endl;

    return 0;
}
