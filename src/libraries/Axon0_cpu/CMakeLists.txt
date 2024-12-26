cmake_minimum_required(VERSION 3.16)
project(Axon_cpu VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(Axon_cpu STATIC
    include/Axon_cpu/cpu.h
    include/Axon_cpu/memory.h
    include/Axon_cpu/rapl.h
    src/cpu.cpp
    src/memory.cpp
    src/rapl.cpp
)

target_include_directories(Axon_cpu PUBLIC
    include/
    src/
    ../Axon_common/include
)

target_link_libraries(Axon_cpu PUBLIC
    Axon_common
)
