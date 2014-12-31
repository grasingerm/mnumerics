cmake_minimum_required(VERSION 2.8)

project(mnumerics)

set(CC clang)
set(CSTD c11)

# set flags for warnings, errors, and standards
if( NOT CMAKE_BUILD_TYPE )
  set( CMAKE_BUILD_TYPE release CACHE STRING
       "Choose the type of build, options are: None Debug Release RelWithDebInfo
        MinSizeRel."
       FORCE )
endif()

set(CMAKE_C_FLAGS_DEBUG "-Wall -Wextra -g -std=${CSTD} -pedantic -pedantic-errors")
set(CMAKE_C_FLAGS_RELEASE "-Wall -Wextra -std=${CSTD} -pedantic -pedantic-errors -O3")

# build directories
set(CMAKE_BINARY_DIR build)
set(EXECUTABLE_OUTPUT_PATH bin)

# include and link directories
include_directories(../include)

add_library(mnumerics SHARED ../src/mnumerics.c ../src/vector.c)
add_executable(test_vector test_vector.c)
add_executable(test_mnumerics test_mnumerics.c)

if (UNIX)
    target_link_libraries(mnumerics m)
    target_link_libraries(test_vector m)
endif (UNIX)

target_link_libraries(test_vector mnumerics)
target_link_libraries(test_mnumerics mnumerics)
