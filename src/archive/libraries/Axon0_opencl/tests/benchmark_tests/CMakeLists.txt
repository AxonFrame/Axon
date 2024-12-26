qt_add_executable(benchmark_tests
    main.cpp
    simple_test.cpp simple_test.h
)
target_include_directories(benchmark_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ../../../Axon_common/include
    ../../include
    ../../src
)

target_link_libraries(benchmark_tests PRIVATE
    # Remove: L../../../Axon_common/src
    # Remove: L../../../Axon_common/src/debug
    # Remove: L../../../Axon_common/src/release
    # Remove: L../../src
    # Remove: qt
    OpenCL
    Axon_common
    Axon_opencl
)

install(TARGETS benchmark_tests
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

qt_generate_deploy_app_script(
    TARGET benchmark_tests
    FILE_VARIABLE deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
