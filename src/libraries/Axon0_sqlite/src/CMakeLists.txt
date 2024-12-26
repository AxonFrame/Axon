qt_add_library(Axon_sqlite
    ../include/Axon_sqlite/sqlite.h
    sqlite.cpp
)
target_include_directories(Axon_sqlite PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ../../../third-party-libs/json/include
    ../../Axon_common/include
    ../include
)

target_link_libraries(Axon_sqlite PUBLIC
    # Remove: L../../Axon_common/src
    # Remove: L../../Axon_common/src/debug
    # Remove: L../../Axon_common/src/release
    # Remove: qt
    SQLite::SQLite3
    Axon_common
)

install(TARGETS Axon_sqlite
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    FRAMEWORK DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
