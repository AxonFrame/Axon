cmake_minimum_required(VERSION 3.16)
project(Axon_cluster_parser VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_library(Axon_cluster_parser STATIC
    include/Axon_cluster_parser/cluster_meta.h
    src/cluster_meta.cpp
    src/cluster_parsing/cluster_parser_interface.h
    src/cluster_parsing/cluster_parser_interface.cpp
    src/grammar/cluster_lexer.l
    src/grammar/cluster_parser.y
)

target_include_directories(Axon_cluster_parser PUBLIC
    include/
    src/
    ../Axon_common/include
)

target_link_libraries(Axon_cluster_parser PUBLIC
    Axon_common
)

# Flex and Bison commands
find_program(FLEX_EXECUTABLE S flex)
find_program(BISON_EXECUTABLE S bison)

if(FLEX_EXECUTABLE AND BISON_EXECUTABLE)
    set(FLEX_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/src/grammar/cluster_lexer.l)
    set(FLEX_OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/cluster_lexer.cpp)

    set(BISON_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/src/grammar/cluster_parser.y)
    set(BISON_OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/cluster_parser.cpp)

    add_custom_command(
        OUTPUT ${FLEX_OUTPUT} ${BISON_OUTPUT}
        COMMAND ${BISON_EXECUTABLE} -d --defines=${CMAKE_CURRENT_BINARY_DIR}/cluster_parser.h -o ${BISON_OUTPUT} ${BISON_INPUT}
        # COMMAND ${BISON_EXECUTABLE} -Wcounterexamples -d --defines=${CMAKE_CURRENT_BINARY_DIR}/cluster_parser.h -o ${BISON_OUTPUT} ${BISON_INPUT}
        COMMAND ${FLEX_EXECUTABLE} --header-file=${CMAKE_CURRENT_BINARY_DIR}/cluster_lexer.h -o ${FLEX_OUTPUT} ${FLEX_INPUT}
        DEPENDS ${FLEX_INPUT} ${BISON_INPUT}
    )

    # Add dependencies on the targets representing the generated files
    add_custom_target(generate_cluster_flex_bison_files DEPENDS ${FLEX_OUTPUT} ${BISON_OUTPUT})

    # Make Axon_cluster_parser depend on the custom target
    add_dependencies(Axon_cluster_parser generate_cluster_flex_bison_files)

    target_sources(Axon_cluster_parser PRIVATE ${FLEX_OUTPUT} ${BISON_OUTPUT})

endif()

if(run_tests)
    add_subdirectory(tests)
endif()
