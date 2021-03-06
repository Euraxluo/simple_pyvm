cmake_minimum_required(VERSION 3.10.2)
project(simple_pyvm)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)
include_directories(src/object)
include_directories(src/util)

add_executable(simple_pyvm
        main.cpp

        src/code/bytecode.hpp
        src/code/codeObject.hpp
        src/code/binaryFileParser.hpp

        src/util/hashMap.hpp
        src/util/arrayList.hpp
        src/util/bufferedInputStream.cpp
        src/util/bufferedInputStream.hpp
        src/util/heap.hpp
        src/util/helper.hpp

        src/runtime/interpreter.cpp
        src/runtime/interpreter.hpp
        src/runtime/universe.cpp
        src/runtime/universe.hpp
        src/runtime/frameObject.hpp

        src/object/object.cpp
        src/object/object.hpp
        src/object/integer.cpp
        src/object/integer.hpp
        src/object/string.cpp
        src/object/string.hpp
        src/object/function.cpp
        src/object/function.hpp
        src/object/method.cpp
        src/object/method.hpp
        src/object/klass.hpp
        src/object/checkKlass.hpp
        src/object/list.cpp
        src/object/list.hpp
        src/object/klass.cpp
        src/runtime/stringTable.cpp
        src/runtime/stringTable.hpp
        src/object/map.cpp
        src/object/map.hpp
        src/object/cell.cpp
        src/object/cell.hpp
        src/object/type.cpp
        src/object/type.hpp
        src/object/module.cpp
        src/object/module.hpp)


#ADD_CUSTOM_COMMAND(TARGET math
#        POST_BUILD
#        COMMAND mkdir -p lib
#        COMMAND cp libmath.so lib/
#        COMMAND cp ../lib/*.py lib/
#        COMMAND python -m compileall lib/*.py
#        )