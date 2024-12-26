add_executable(Axon_sqlite_unit_tests
    sqlite_test.cpp
    sqlite_test.h
    main.cpp
)

target_include_directories(Axon_sqlite_unit_tests PRIVATE
    ../../include/
    ../../src/
)

target_link_libraries(Axon_sqlite_unit_tests PRIVATE
    Axon_sqlite
    Axon_common
)
