add_executable(Axon_database_functional_tests
    sql_table_test.cpp
    sql_table_test.h
    test_table.cpp
    test_table.h
    main.cpp
)

target_include_directories(Axon_database_functional_tests PRIVATE
    ../../include/
    ../../src/
)

target_link_libraries(Axon_database_functional_tests PRIVATE
    Axon_database
    Axon_common
)
