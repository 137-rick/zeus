project(zeus)
#SET(CMAKE_BUILD_TYPE "Debug")

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -W -Wall -W ")

set(CMAKE_EXE_LINKER_FLAGS "-pthread")

set(SOURCE_FILES1 zeus.cpp zeus.hpp zsepoll.hpp zsepoll.cpp zssocket.cpp zssocket.h)
add_executable(zeus ${SOURCE_FILES1})
