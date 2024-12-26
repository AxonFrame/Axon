qt_add_library(Axon_obj
    ../include/Axon_obj/obj_item.h
    obj_creator.cpp obj_creator.h
    obj_item.cpp
    obj_parser.cpp obj_parser.h
)
target_include_directories(Axon_obj PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ../../Axon_common/include
    ../include
)

target_link_libraries(Axon_obj PUBLIC
    # Remove: L../../Axon_common/src
    # Remove: L../../Axon_common/src/debug
    # Remove: L../../Axon_common/src/release
    # Remove: qt
    Axon_common
)

install(TARGETS Axon_obj
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    FRAMEWORK DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
