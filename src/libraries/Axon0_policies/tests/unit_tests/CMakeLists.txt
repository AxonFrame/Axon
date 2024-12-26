add_executable(Axon_policies_unit_tests
    policy_test.cpp
    policy_test.h
    main.cpp
)

target_include_directories(Axon_policies_unit_tests PRIVATE
    ../../include/
    ../../src/
)

target_link_libraries(Axon_policies_unit_tests PRIVATE
    Axon_policies
    Axon_common
)
