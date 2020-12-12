cmake_minimum_required(VERSION 3.10.2)
project(simple_pyvm)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)
include_directories(src/object)
include_directories(src/study)
include_directories(src/util)

add_executable(simple_pyvm
        src/object/object.hpp
        src/object/string.hpp
        src/study/study.hpp
        src/util/arrayList.hpp
        src/util/bufferedInputStream.hpp
        main.cpp src/util/heap.hpp src/object/integer.hpp src/code/codeObject.hpp src/code/binaryFileParser.hpp src/util/dumpHex.hpp src/util/helper.hpp)
