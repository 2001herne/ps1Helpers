cmake_minimum_required(VERSION 3.17)
project(ps1Helpers)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BUILD_)

add_executable(ps1_mainline src/ps1_mainline.cpp src/Common.cpp)
target_include_directories(ps1_mainline PRIVATE include)
install(TARGETS ps1_mainline DESTINATION bin)

add_executable(ps1_gitline src/ps1_gitline.cpp src/Common.cpp)
target_include_directories(ps1_gitline PRIVATE include)
target_link_libraries(ps1_gitline git2)