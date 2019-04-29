#cmake_minimum_required(VERSION 3.8)
project(zeus)

#set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "-std=c99 -std=c++11 -Wall -W -static-libstdc++")
set(CMAKE_EXE_LINKER_FLAGS "-pthread")
#set(SOURCE_FILES main.c.bak socket.h.bak)
#add_executable(socket ${SOURCE_FILES})

set(SOURCE_FILES1 zeus.cpp zeus.hpp zsepoll.hpp zsepoll.cpp zssocket.cpp zssocket.h)
add_executable(zeus ${SOURCE_FILES1})
