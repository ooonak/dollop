cmake_minimum_required(VERSION 3.24)

project(DollopApp LANGUAGES CXX)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE dp::Controller)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)

