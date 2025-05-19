cmake_minimum_required(VERSION 3.31)
project(ShredStorm)

set(CMAKE_CXX_STANDARD 20)

add_executable(ShredStorm main.cpp
        src/ui.cpp
        include/ui.h
        include/tab.h
        src/tab.cpp
        include/consts.h
        include/argsHandling.h
        src/argsHandling.cpp)
