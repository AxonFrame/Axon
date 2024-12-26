cmake_minimum_required(VERSION 3.16)
project(Axon_args VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(Axon_args STATIC
    include/Axon_args/arg_parser.h
    src/arg_parser.cpp
)

target_include_directories(Axon_args PUBLIC
    include/
    src/
    ../Axon_common/include
)

target_link_libraries(Axon_args PUBLIC
    Axon_common
)

if(run_tests)
    add_subdirectory(tests)
endif()
