cmake_minimum_required(VERSION 3.24)

project(DollopController LANGUAGES CXX)

option(BUILD_TESTS "Build test programs" OFF)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(MANAGE_DEPENDENCIES_WITH_FETCH_CONTENT ON)

set(FETCHCONTENT_TRY_FIND_PACKAGE_MODE NEVER)
set(msgpack_MSGPACK_CXX20 ON)
set(msgpack_MSGPACK_BUILD_DOCS OFF)

include(Dependencies.cmake)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}")
include(snippets)

#enable_clang_tidy()
#enable_cppcheck()
#enable_iwyu()

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wnull-dereference")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wshadow -Wunused -Wnon-virtual-dtor -Woverloaded-virtual")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wold-style-cast -Wcast-qual -Wcast-align -Wsign-conversion")

if (${CMAKE_BUILD_TYPE} STREQUAL "Release")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O1")
endif()

message(STATUS "CXX flags: ${CMAKE_CXX_FLAGS}")

add_subdirectory(src)
add_subdirectory(app)
add_subdirectory(test)

if(BUILD_TESTS)
    include(CTest)
    enable_testing()
    add_subdirectory(test)
endif(BUILD_TESTS)

