cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 14)
project(container)
if(POLICY
   CMP0074)

  cmake_policy(
    SET
    CMP0074
    NEW)
else()
  cmake_policy(
    SET
    CMP0065
    NEW)
endif()

# TODO set(CMAKE_BUILD_TYPE ON)

find_package(
  Boost
  REQUIRED
  COMPONENTS system
             filesystem
             thread
             iostreams)

# ================================================================================
set(Boost_INCLUDE_DIRS "/usr/lib/x86_64-linux-gnu/")

# add_definitions(-DQT_MESSAGELOGCONTEXT)
add_definitions(-g)

include_directories(
  ./
  include)
  #src)
# ${OPENSSL_INCLUDE_DIR} ${Boost_INCLUDE_DIRS})

add_library(
  container_lib
  #src/ring.cc)
  src/ring_2d_shared.cc
  src/ring_2dex.cc)
set_target_properties(
  container_lib
  PROPERTIES CXX_STANDARD_REQUIRED
             TRUE
             CXX_STANDARD
             14)

# Property include_directories(${PROJECT_SOURCE_DIR})
