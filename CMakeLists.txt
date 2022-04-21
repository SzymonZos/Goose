cmake_minimum_required(VERSION 3.19)
if(DEFINED GOS_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD ${GOS_CXX_STANDARD})
else()
    set(CMAKE_CXX_STANDARD 20)
endif()

option(GOS_BUILD_TESTS OFF)
option(GOS_USE_LIBCPP OFF)
project(goose VERSION "0.1.0")

add_library(goose INTERFACE)
target_include_directories(goose INTERFACE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
)

if(GOS_BUILD_TESTS)
    add_subdirectory(test)
endif()
