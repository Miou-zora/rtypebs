cmake_minimum_required(VERSION 3.10)
project(untitled)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Werror -Wextra -Wshadow -Wuninitialized")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

set(INCLUDE
    "src/"
    "src/Component/"
    "src/System/"
)

include_directories(${INCLUDE})

set(MAIN "main.cpp")



add_executable(untitled ${MAIN} ${SRC})
find_package(SFML COMPONENTS graphics window system REQUIRED)
target_link_libraries(untitled sfml-graphics sfml-window sfml-system)

