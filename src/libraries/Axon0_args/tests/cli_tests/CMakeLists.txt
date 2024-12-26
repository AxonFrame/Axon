add_executable(Axon_args_cli_tests
    main.cpp
)

target_include_directories(Axon_args_cli_tests PRIVATE
    ../../include/
    ../../src/
)

target_link_libraries(Axon_args_cli_tests PRIVATE
    Axon_args
    Axon_common
)
