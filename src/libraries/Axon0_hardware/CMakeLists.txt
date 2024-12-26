cmake_minimum_required(VERSION 3.16)
project(Axon_hardware VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(Axon_hardware STATIC
    include/Axon_hardware/cpu_core.h
    include/Axon_hardware/cpu_package.h
    include/Axon_hardware/cpu_thread.h
    include/Axon_hardware/host.h
    include/Axon_hardware/power_measuring.h
    include/Axon_hardware/speed_measuring.h
    include/Axon_hardware/temperature_measuring.h
    include/Axon_hardware/value_container.h
    src/cpu_core.cpp
    src/cpu_package.cpp
    src/cpu_thread.cpp
    src/host.cpp
    src/power_measuring.cpp
    src/speed_measuring.cpp
    src/temperature_measuring.cpp
    src/value_container.cpp
)

target_include_directories(Axon_hardware PUBLIC
    include/
    src/
    ../Axon_common/include
    ../Axon_cpu/include
)

target_link_libraries(Axon_hardware PUBLIC
    Axon_common
    Axon_cpu
)
