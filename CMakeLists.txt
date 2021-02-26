#   CMakeLists.txt - Contains CMake configuration for whole project
#   Copyright 2021 Benjamin Herne
#
#   Licensed under the Apache License, Version 2.0 (the "License");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
#
#       http://www.apache.org/licenses/LICENSE-2.0
#
#   Unless required by applicable law or agreed to in writing, software
#   distributed under the License is distributed on an "AS IS" BASIS,
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#   See the License for the specific language governing permissions and
#   limitations under the License.


cmake_minimum_required(VERSION 3.17)
project(ps1Helpers)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BUILD_)

add_executable(ps1_mainline src/ps1_mainline.cpp src/Common.cpp)
target_include_directories(ps1_mainline PRIVATE include)

add_executable(ps1_gitline src/ps1_gitline.cpp src/Common.cpp)
target_include_directories(ps1_gitline PRIVATE include)
target_link_libraries(ps1_gitline git2)

install(TARGETS ps1_mainline ps1_gitline DESTINATION bin)