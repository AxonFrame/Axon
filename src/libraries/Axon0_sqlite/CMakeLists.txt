cmake_minimum_required(VERSION 3.16)
project(Axon_sqlite VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(Axon_sqlite STATIC
    include/Axon_sqlite/sqlite.h
    src/sqlite.cpp
)

target_include_directories(Axon_sqlite PUBLIC
    include/
    src/
    ../Axon_common/include
)

target_link_libraries(Axon_sqlite PUBLIC
    Axon_common
    sqlite3
)

if(run_tests)
    add_subdirectory(tests)
endif()
