qt_add_library(Axon_database
    ../include/Axon_database/sql_database.h
    ../include/Axon_database/sql_table.h
    sql_database.cpp
    sql_table.cpp
)
target_include_directories(Axon_database PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ../../../third-party-libs/json/include
    ../../Axon_common/include
    ../../Axon_sqlite/include
    ../include
)

target_link_libraries(Axon_database PUBLIC
    # Remove: L../../Axon_common/src
    # Remove: L../../Axon_common/src/debug
    # Remove: L../../Axon_common/src/release
    # Remove: L../../Axon_sqlite/src
    # Remove: L../../Axon_sqlite/src/debug
    # Remove: L../../Axon_sqlite/src/release
    # Remove: qt
    SQLite::SQLite3
    Axon_common
    Axon_sqlite
)

install(TARGETS Axon_database
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    FRAMEWORK DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
