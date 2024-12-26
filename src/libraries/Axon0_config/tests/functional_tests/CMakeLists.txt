add_executable(Axon_config_functional_tests
    config_handler_test.cpp
    config_handler_test.h
    main.cpp
)

target_include_directories(Axon_config_functional_tests PRIVATE
    ../../include/
    ../../src/
)

target_link_libraries(Axon_config_functional_tests PRIVATE
    Axon_config
    Axon_common
)
