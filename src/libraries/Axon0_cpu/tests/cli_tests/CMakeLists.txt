qt_add_executable(cli_tests
    main.cpp
)
target_include_directories(cli_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ../../../../third-party-libs/json/include
    ../../../Axon_common/include
    ../../include
    ../../src
)

target_link_libraries(cli_tests PRIVATE
    # Remove: L../../../Axon_common/src
    # Remove: L../../../Axon_common/src/debug
    # Remove: L../../../Axon_common/src/release
    # Remove: L../../src
    # Remove: qt
    Axon_common
    Axon_cpu
)

install(TARGETS cli_tests
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

qt_generate_deploy_app_script(
    TARGET cli_tests
    FILENAME_VARIABLE deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
