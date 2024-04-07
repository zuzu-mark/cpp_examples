cmake_minimum_required(VERSION 3.8)
project(test)

find_package(Boost REQUIRED COMPONENTS system thread)
#find_package(Threads REQUIRED)

set(Boost_INCLUDE_DIRS
    "/usr/lib/x86_64-linux-gnu/")

include_directories(Boost::boost
../include/
../src/
Logger/include/
 ${Boost_INCLUDE_DIRS})

add_definitions(-g)
add_executable(main main.cpp
	Logger/src/logger.cc)
target_link_libraries(main Boost::system #Threads::Threads)
 Boost::thread)

set(TARGETS main)

set_property(TARGET ${TARGETS} PROPERTY CXX_STANDARD 17)
set_property(TARGET ${TARGETS} PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${TARGETS} PROPERTY CXX_EXTENSION OFF)

