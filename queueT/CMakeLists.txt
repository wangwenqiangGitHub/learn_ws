cmake_minimum_required(VERSION 2.6)
 # 工程vscode_cmake
project(vscode_cmake)

#dubug 模式
set (CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -g")

SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

include_directories(./src)

set(SRC_LIST 
src/main.cpp                
src/printf.cpp)
# 可执行程序 result
add_executable(result ${SRC_LIST})