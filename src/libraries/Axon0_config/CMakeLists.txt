cmake_minimum_required(VERSION 3.16)
project(Axon_config VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(Axon_config STATIC
    include/Axon_config/config_handler.h
    src/config_handler.cpp
)

target_include_directories(Axon_config PUBLIC
    include/
    src/
    ../Axon_common/include
    ../Axon_ini/include
)

target_link_libraries(Axon_config PUBLIC
    Axon_common
    Axon_ini
)

if(run_tests)
    add_subdirectory(tests)
endif()
