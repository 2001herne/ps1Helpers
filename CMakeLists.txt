cmake_minimum_required(VERSION 3.17)
project(ps1Helpers)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BUILD_)

add_executable(PS1Main src/ps1Main.cpp src/Common.cpp include/Common.h)

target_include_directories(PS1Main PRIVATE include)

install(TARGETS PS1Main DESTINATION bin)