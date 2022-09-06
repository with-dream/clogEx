cmake_minimum_required(VERSION 3.16.2)
project(logEx)

set(CMAKE_CXX_STANDARD 11)
#../../src/config/config.c ../../src/config/config.h ../../src/utils/hash_map.c ../../src/utils/hash_map.h ../../src/utils/type.h ../../src/utils/hash_map_str.c ../../src/utils/hash_map_str.h

set(src_list
        ../../third_party/tinyxml2/tinyxml2.cpp
        ../../third_party/tinyxml2/tinyxml2.h
        ../../src/config/Level.h
        ../../src/utils/StrUtils.h
        ../../src/appender/Appender.cpp
        ../../src/appender/Appender.h
        ../../src/config/ConfigFactory.cpp
        ../../src/config/ConfigFactory.h
        ../../src/appender/Console.cpp
        ../../src/appender/Console.h
        ../../src/filter/Filter.cpp
        ../../src/filter/Filter.h
        ../../src/layout/Layout.cpp
        ../../src/layout/Layout.h
        ../../src/policy/Policy.cpp
        ../../src/policy/Policy.h
        ../../src/config/Parse.h
        ../../src/config/Parse.cpp
        ../../src/logger/Logger.cpp
        ../../src/logger/Logger.h
        ../../src/config/TinyXmlParse.cpp
        ../../src/config/TinyXmlParse.h
        ../../src/config/Param.h
        ../../src/utils/Exception.cpp
        ../../src/utils/Exception.h
        ../../src/filter/ThresholdFilter.cpp
        ../../src/filter/ThresholdFilter.h
        ../../src/layout/PatternLayout.cpp
        ../../src/layout/PatternLayout.h
        ../../src/config/ConfigFactory.cpp
        ../../src/config/ConfigFactory.h
        ../../src/LogManager.cpp
        ../../src/LogManager.h
        ../../src/message/MessageFactory.cpp
        ../../src/message/MessageFactory.h
        ../../src/config/LoggerConfig.cpp
        ../../src/config/LoggerConfig.h
        ../../src/message/Message.cpp
        ../../src/message/Message.h
        ../../src/marker/Marker.cpp
        ../../src/marker/Marker.h)

add_executable(logEx
        ${src_list}
        main.cpp)
