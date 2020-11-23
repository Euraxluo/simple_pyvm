cmake_minimum_required(VERSION 3.13)
project(pythonvm)

set(CMAKE_CXX_STANDARD 14)

add_executable(pythonvm main.cpp src/util/BufferedInputStream.hpp src/study/Study.hpp src/util/ArrayList.hpp src/object/HiObject.hpp src/object/HiString.hpp)