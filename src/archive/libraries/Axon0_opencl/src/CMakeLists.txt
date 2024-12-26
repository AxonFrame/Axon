qt_add_library(Axon_opencl
    ../include/Axon_opencl/gpu_data.h
    ../include/Axon_opencl/gpu_handler.h
    ../include/Axon_opencl/gpu_interface.h
    gpu_data.cpp
    gpu_handler.cpp
    gpu_interface.cpp
)
target_include_directories(Axon_opencl PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ../../Axon_common/include
    ../include
)

target_link_libraries(Axon_opencl PUBLIC
    # Remove: L../../Axon_common/src
    # Remove: L../../Axon_common/src/debug
    # Remove: L../../Axon_common/src/release
    # Remove: qt
    OpenCL
    Axon_common
)

install(TARGETS Axon_opencl
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    FRAMEWORK DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
