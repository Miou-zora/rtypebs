cmake_minimum_required(VERSION 3.10)
project(untitled)

if(UNIX)
  # Add file textension *.bin to all executables on Unix (Linux, OSX, BSD ...)
  set(CMAKE_EXECUTABLE_SUFFIX ".bin")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Werror -Wextra -Wshadow -Wuninitialized -ldl -lpthread")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

set(INCLUDE
    "src/"
    "src/Component/"
    "src/System/"
    "src/Component/Tag/"
)

include_directories(${INCLUDE})

set(MAIN "main.cpp")

find_package(Boost 1.82.0 REQUIRED COMPONENTS system thread filesystem)
find_package(GTest CONFIG REQUIRED)
find_package(raylib CONFIG REQUIRED)
find_package(CMakeRC)

cmrc_add_resource_library(
    app1-resources

    ALIAS app1::rc
    NAMESPACE app1

    assets/player.png
    assets/enemy.png
)

add_executable(untitled ${MAIN} ${SRC})
target_link_libraries(untitled app1::rc)
enable_testing()

set(TEST_MAIN
    "tests/main.cpp"
)

set(TEST_SRC
    "tests/test_sparse_array.cpp"
)

add_executable(test_rtype_server ${TEST_MAIN} ${SRC} ${TEST_SRC})
target_link_libraries(test_rtype_server GTest::gtest GTest::gtest_main)
add_test(NAME r-type_server_test COMMAND test_rtype_server)
target_link_libraries(untitled raylib)

