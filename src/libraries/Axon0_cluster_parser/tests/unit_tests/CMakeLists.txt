add_executable(Axon_cluster_parser_unit_tests
    cluster_parsestring_test.cpp
    cluster_parsestring_test.h
    main.cpp
)

target_include_directories(Axon_cluster_parser_unit_tests PRIVATE
    ../../include/
    ../../src/
)

target_link_libraries(Axon_cluster_parser_unit_tests PRIVATE
    Axon_cluster_parser
    Axon_common
)
