cmake_minimum_required(VERSION 3.5)

project(PA2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 REQUIRED COMPONENTS Sql)

add_executable(PA2 main.cpp client.h client.cpp robot.h robot.cpp)
target_link_libraries(PA2  Qt5::Core Qt5::Sql)
