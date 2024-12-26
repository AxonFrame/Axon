add_executable(Axon_ini_unit_tests
    Axon_ini/ini_item_test.cpp
    Axon_ini/ini_item_test.h
    main.cpp
)

target_include_directories(Axon_ini_unit_tests PRIVATE
    ../../include/
    ../../src/
)

target_link_libraries(Axon_ini_unit_tests PRIVATE
    Axon_ini
    Axon_common
)

