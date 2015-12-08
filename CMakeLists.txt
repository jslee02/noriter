#===============================================================================
# CMake settings
#===============================================================================
cmake_minimum_required(VERSION 2.8.6 FATAL_ERROR)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include(${CMAKE_MODULE_PATH}/NoriterMacros.cmake)

#===============================================================================
# Project settings
#===============================================================================
project(noriter)

# The version number.
set(NORITER_VERSION_MAJOR 0)
set(NORITER_VERSION_MINOR 1)
set(NORITER_VERSION_PATCH 0)
set(NORITER_VERSION
    "${NORITER_VERSION_MAJOR}.${NORITER_VERSION_MINOR}.${NORITER_VERSION_MAJOR}")

#===============================================================================
# Print intro
#===============================================================================
message(STATUS "")
message(STATUS "============================================")
message(STATUS "               ${PROJECT_NAME} ${NORITER_VERSION}")
message(STATUS "============================================")

#===============================================================================
# Build options
#===============================================================================
option(NORITER_BUILD_STATIC_LIBS "Build static libraries" OFF)
option(NORITER_BUILD_TESTS "Build tests" ON)
option(NORITER_CODE_COVERAGE "Build with code coverage test" OFF)

#===============================================================================
# Find dependencies
#===============================================================================

#------------------------
# Mandatory dependencies
#------------------------
message(STATUS "")
message(STATUS "[ Mandatory dependencies ]")

# Eigen
find_package(EIGEN3 3.0.5 QUIET)
if(EIGEN3_FOUND)
  message(STATUS "Looking for EIGEN3 - ${EIGEN3_VERSION} found")
else()
  if(PC_EIGEN3_VERSION)
    message(SEND_ERROR "Looking for EIGEN3 - ${EIGEN3_VERSION} found, ${PROJECT_NAME} requires 3.0.5 or greater.")
  else()
    message(SEND_ERROR "Looking for EIGEN3 - NOT found, please install libeigen3-dev")
  endif()
endif()

#===============================================================================
# Include directories
#===============================================================================
include_directories(BEFORE ${PROJECT_SOURCE_DIR}/include)
include_directories(SYSTEM ${EIGEN3_INCLUDE_DIRS})

include_directories("${CMAKE_BINARY_DIR}/include")

#===============================================================================

# configure a header file to pass some of the CMake settings
# to the source code
configure_file(
  "${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/Config.h.in"
  "${PROJECT_BINARY_DIR}/include/${PROJECT_NAME}/Config.h"
  )

if(NORITER_CODE_COVERAGE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -coverage")
endif(NORITER_CODE_COVERAGE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

message(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
include_directories("${PROJECT_BINARY_DIR}")
 
# add the executable
add_subdirectory(include/noriter)
add_subdirectory(src)

# tests
if(NORITER_BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif(NORITER_BUILD_TESTS)
