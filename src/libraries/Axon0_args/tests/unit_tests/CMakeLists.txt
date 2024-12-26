add_executable(Axon_args_unit_tests
    arg_parser_test.cpp
    arg_parser_test.h
    main.cpp
)

target_include_directories(Axon_args_unit_tests PRIVATE
    ../../include/
    ../../src/
)

target_link_libraries(Axon_args_unit_tests PRIVATE
    Axon_args
    Axon_common
)
