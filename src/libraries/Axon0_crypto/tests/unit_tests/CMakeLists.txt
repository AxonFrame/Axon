add_executable(Axon_crypto_unit_tests
    common_test.cpp
    common_test.h
    hashes_test.cpp
    hashes_test.h
    main.cpp
    symmetric_encryption_test.cpp
    symmetric_encryption_test.h
)

target_include_directories(Axon_crypto_unit_tests PRIVATE
    ../../../Axon_common/include
    ../../include
    ../../src
)

target_link_libraries(Axon_crypto_unit_tests PRIVATE
    crypto
    cryptopp
    Axon_common
    Axon_crypto
    ssl
)
