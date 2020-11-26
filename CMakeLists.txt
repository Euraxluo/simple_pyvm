cmake_minimum_required(VERSION 3.13)
project(simple_pyvm)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)
include_directories(src/object)
include_directories(src/study)
include_directories(src/util)

add_executable(simple_pyvm
        src/object/Object.hpp
        src/object/String.hpp
        src/study/Study.hpp
        src/util/ArrayList.hpp
        src/util/BufferedInputStream.hpp
        main.cpp src/util/heap.hpp)
