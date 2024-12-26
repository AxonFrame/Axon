cmake_minimum_required(VERSION 3.16)
project(Axon_crypto VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(Axon_crypto STATIC
    include/Axon_crypto/common.h
    include/Axon_crypto/hashes.h
    include/Axon_crypto/signing.h
    include/Axon_crypto/symmetric_encryption.h
    src/common.cpp
    src/hashes.cpp
    src/symmetric_encryption.cpp
)

target_include_directories(Axon_crypto PUBLIC
    include/
    src/
    ../Axon_common/include
)

target_link_libraries(Axon_crypto PUBLIC
    crypto
    cryptopp
    Axon_common
    ssl
)

if(run_tests)
    add_subdirectory(tests)
endif()
