cmake_minimum_required(VERSION 3.16)
project(Axon_database VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(Axon_database STATIC
    include/Axon_database/sql_database.h
    include/Axon_database/sql_table.h
    src/sql_database.cpp
    src/sql_table.cpp
)

target_include_directories(Axon_database PUBLIC
    include/
    src/
    ../Axon_common/include
    ../Axon_sqlite/include
)

target_link_libraries(Axon_database PUBLIC
    Axon_common
    Axon_sqlite
    Axon_crypto
)

if(run_tests)
    add_subdirectory(tests)
endif()
