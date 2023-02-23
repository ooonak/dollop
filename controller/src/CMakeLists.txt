cmake_minimum_required(VERSION 3.24)

project(Controller VERSION 0.0.1 LANGUAGES CXX)

file(WRITE ${PROJECT_BINARY_DIR}/dollopcontrollerconfig.hpp.in "
#pragma once

#define DollopController_VERSION_MAJOR @DollopController_VERSION_MAJOR@
#define DollopController_VERSION_MINOR @DollopController_VERSION_MINOR@
#define DollopController_VERSION_PATCH @DollopController_VERSION_PATCH@
")

find_package(Threads REQUIRED)
find_package(Boost REQUIRED)

# https://raw.githubusercontent.com/facebookincubator/fizz/main/build/fbcode_builder/CMake/FindSodium.cmake
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR};${CMAKE_MODULE_PATH}")
find_package(Sodium REQUIRED)

add_library(${PROJECT_NAME}
    include/dp/Controller.hpp
    Controller.cpp
    Config.hpp
    Message.hpp
    Communicator.hpp
    CommunicatorAsio.cpp CommunicatorAsio.hpp
)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

target_include_directories(${PROJECT_NAME}
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}>
    $<INSTALL_INTERFACE:include>
    ${toml_SOURCE_DIR}
    ${sodium_INCLUDE_DIR}
    ${Boost_INCLUDE_DIRS}
    ${spdlog_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME}
   PRIVATE
   Threads::Threads
   ${sodium_LIBRARY_RELEASE}
   spdlog::spdlog
   msgpackc-cxx
)

add_library(dp::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

configure_file("${PROJECT_BINARY_DIR}/dollopcontrollerconfig.hpp.in" dollopcontrollerconfig.hpp)

install(TARGETS ${PROJECT_NAME}
        EXPORT ${CMAKE_PROJECT_NAME}Targets
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(DIRECTORY include/dp
        DESTINATION include
        COMPONENT Devel
)

