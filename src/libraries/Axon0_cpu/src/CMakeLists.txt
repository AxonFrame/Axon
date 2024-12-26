qt_add_library(Axon_cpu
    ../include/Axon_cpu/cpu.h
    ../include/Axon_cpu/memory.h
    ../include/Axon_cpu/rapl.h
    cpu.cpp
    memory.cpp
    rapl.cpp
)
target_include_directories(Axon_cpu PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ../../../third-party-libs/json/include
    ../../Axon_common/include
    ../include
)

target_link_libraries(Axon_cpu PUBLIC
    # Remove: L../../Axon_common/src
    # Remove: L../../Axon_common/src/debug
    # Remove: L../../Axon_common/src/release
    # Remove: qt
    Axon_common
)

install(TARGETS Axon_cpu
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    FRAMEWORK DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
