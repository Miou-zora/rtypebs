cmake_minimum_required(VERSION 3.10)
project(untitled)

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

set(RAYLIB_VERSION 4.5.0)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
  include(FetchContent)
  FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
  )
  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(raylib)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
    add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
  endif()
endif()

add_executable(untitled ${MAIN} ${SRC})
enable_testing()

set(TEST_MAIN
    "tests/main.cpp"
)

set(TEST_SRC
    "tests/test_sparse_array.cpp"
)

add_executable(test_rtype_server ${TEST_MAIN} ${SRC} ${TEST_SRC})
target_link_libraries(test_rtype_server gtest gtest_main)
add_test(NAME r-type_server_test COMMAND test_rtype_server)
target_link_libraries(untitled raylib)

