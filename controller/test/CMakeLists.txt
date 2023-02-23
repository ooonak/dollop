cmake_minimum_required(VERSION 3.24)

project(DollopControllerUnitTests LANGUAGES CXX)

find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME} ControllerUnitTests.cpp)

target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${CMAKE_SOURCE_DIR}/src
    ${googletest_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
  PRIVATE
  dp::Controller
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})
