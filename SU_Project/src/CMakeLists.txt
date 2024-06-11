cmake_minimum_required(VERSION 3.5)

project(src LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 REQUIRED COMPONENTS Core Sql)

add_executable(src main.cpp game.h character.h hero.h enemy.h dungeon.h magic.h)
target_link_libraries(src Qt5::Core Qt5::Sql)
