cmake_minimum_required(VERSION 3.16.2)
project(logEx C)

set(CMAKE_C_STANDARD 99)

add_executable(logEx ../../src/config/config.c ../../src/config/config.h ../../src/utils/hash_map.c ../../src/utils/hash_map.h ../../src/utils/type.h ../../src/utils/hash_map_str.c ../../src/utils/hash_map_str.h
        main.c)
