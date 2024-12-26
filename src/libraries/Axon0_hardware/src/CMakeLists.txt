qt_add_library(Axon_hardware
    ../include/Axon_hardware/cpu_core.h
    ../include/Axon_hardware/cpu_package.h
    ../include/Axon_hardware/cpu_thread.h
    ../include/Axon_hardware/host.h
    ../include/Axon_hardware/power_measuring.h
    ../include/Axon_hardware/speed_measuring.h
    ../include/Axon_hardware/temperature_measuring.h
    ../include/Axon_hardware/value_container.h
    cpu_core.cpp
    cpu_package.cpp
    cpu_thread.cpp
    host.cpp
    power_measuring.cpp
    speed_measuring.cpp
    temperature_measuring.cpp
    value_container.cpp
)
target_include_directories(Axon_hardware PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ../../../third-party-libs/json/include
    ../../Axon_common/include
    ../../Axon_cpu/include
    ../include
)

target_link_libraries(Axon_hardware PUBLIC
    # Remove: L../../Axon_common/src
    # Remove: L../../Axon_common/src/debug
    # Remove: L../../Axon_common/src/release
    # Remove: L../../Axon_cpu/src
    # Remove: L../../Axon_cpu/src/debug
    # Remove: L../../Axon_cpu/src/release
    # Remove: qt
    Axon_common
    Axon_cpu
)

install(TARGETS Axon_hardware
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    FRAMEWORK DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
