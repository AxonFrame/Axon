qt_add_library(Axon_config
    ../include/Axon_config/config_handler.h
    config_handler.cpp
)
target_include_directories(Axon_config PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ../../../third-party-libs/json/include
    ../../Axon_common/include
    ../../Axon_ini/include
    ../include
)

target_link_libraries(Axon_config PUBLIC
    # Remove: L../../Axon_common/src
    # Remove: L../../Axon_common/src/debug
    # Remove: L../../Axon_common/src/release
    # Remove: L../../Axon_ini/src
    # Remove: L../../Axon_ini/src/debug
    # Remove: L../../Axon_ini/src/release
    # Remove: qt
    Axon_common
    Axon_ini
)

install(TARGETS Axon_config
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    FRAMEWORK DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
