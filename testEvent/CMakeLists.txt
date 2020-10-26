cmake_minimum_required(VERSION 2.6)
 # 工程vscode_cmake
project(event_test)

#dubug 模式
set (CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -g -std=c++11")
# set (CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -g -std=c++11 -levent -lpthread")

SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

include_directories(./)

set(SRC_LIST 
main.cc
tcp_client.cc                
tcp_server.cc
comm_util.cc
tcp_message_handler.cc
)
# 可执行程序 result
add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME}
event
pthread
)