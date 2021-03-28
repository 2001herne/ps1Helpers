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

add_library(libps1common src/Common.cpp)
target_include_directories(libps1common PRIVATE include)

add_executable(ps1mainline src/ps1_mainline.cpp)
target_include_directories(ps1mainline PRIVATE include)
add_dependencies(ps1mainline libps1common)
target_link_libraries(ps1mainline libps1common)

add_executable(ps1gitline src/ps1_gitline.cpp)
target_include_directories(ps1gitline PRIVATE include)
add_dependencies(ps1gitline libps1common)
target_link_libraries(ps1gitline libps1common git2)

add_executable(ps1sudoprompt src/ps1_sudoprompt.cpp)
target_include_directories(ps1sudoprompt PRIVATE include)
add_dependencies(ps1sudoprompt libps1common)
target_link_libraries(ps1sudoprompt libps1common)

install(TARGETS libps1common DESTINATION lib)
install(TARGETS ps1mainline ps1gitline ps1sudoprompt DESTINATION bin)