qt_add_executable(functional_tests
    cert_init.h
    main.cpp
    session_test.cpp session_test.h
    tcp/tcp_test.cpp tcp/tcp_test.h
    tls_tcp/tls_tcp_test.cpp tls_tcp/tls_tcp_test.h
    unix/unix_domain_test.cpp unix/unix_domain_test.h
)
target_include_directories(functional_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ../../../Axon_common/include
    ../../include
    ../../src
)

target_link_libraries(functional_tests PRIVATE
    # Remove: L../../../Axon_common/src
    # Remove: L../../../Axon_common/src/debug
    # Remove: L../../../Axon_common/src/release
    # Remove: L../../src
    # Remove: qt
    crypt
    Axon_common
    Axon_network
    ssl
)

install(TARGETS functional_tests
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

qt_generate_deploy_app_script(
    TARGET functional_tests
    FILE_VARIABLE deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
