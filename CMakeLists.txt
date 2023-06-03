cmake_minimum_required(VERSION 3.23)
project(Sznajd_model)

set(CMAKE_CXX_STANDARD 14)

set(PROJECT_HEADERS
        board.hpp
        matplotlibcpp.h)

set(PROJECT_SOURCES
        main.cpp
        board.cpp
        table_utils.cpp
        )

find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

include_directories(.)

add_executable(Sznajd_model main.cpp)

find_package(Python3 COMPONENTS Interpreter Development REQUIRED)
find_package(Python3 COMPONENTS NumPy)



