qt_add_library(Axon_args
    ../include/Axon_args/arg_parser.h
    arg_parser.cpp
)
target_include_directories(Axon_args PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ../../../third-party-libs/json/include
    ../../Axon_common/include
    ../include
)

target_link_libraries(Axon_args PUBLIC
    # Remove: L../../Axon_common/src
    # Remove: L../../Axon_common/src/debug
    # Remove: L../../Axon_common/src/release
    # Remove: qt
    Axon_common
)

install(TARGETS Axon_args
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    FRAMEWORK DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
