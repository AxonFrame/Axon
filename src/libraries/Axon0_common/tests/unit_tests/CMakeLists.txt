add_executable(Axon_common_unit_tests
    Axon_common/buffer/bit_buffer_test.cpp
    Axon_common/buffer/bit_buffer_test.h
    Axon_common/buffer/data_buffer_test.cpp 
    Axon_common/buffer/data_buffer_test.h
    Axon_common/buffer/item_buffer_test.cpp 
    Axon_common/buffer/item_buffer_test.h
    Axon_common/buffer/ring_buffer_test.cpp 
    Axon_common/buffer/ring_buffer_test.h
    Axon_common/buffer/stack_buffer_reserve_test.cpp 
    Axon_common/buffer/stack_buffer_reserve_test.h
    Axon_common/buffer/stack_buffer_test.cpp 
    Axon_common/buffer/stack_buffer_test.h
    Axon_common/files/binary_file_with_directIO_test.cpp 
    Axon_common/files/binary_file_with_directIO_test.h
    Axon_common/files/binary_file_without_directIO_test.cpp 
    Axon_common/files/binary_file_without_directIO_test.h
    Axon_common/files/text_file_test.cpp 
    Axon_common/files/text_file_test.h
    Axon_common/items/table_item_test.cpp 
    Axon_common/items/table_item_test.h
    Axon_common/logger_test.cpp 
    Axon_common/logger_test.h
    Axon_common/functions/file_functions_test.cpp 
    Axon_common/functions/file_functions_test.h
    Axon_common/functions/string_functions_test.cpp 
    Axon_common/functions/string_functions_test.h
    Axon_common/functions/vector_functions_test.cpp 
    Axon_common/functions/vector_functions_test.h
    Axon_common/progress_bar_test.cpp 
    Axon_common/progress_bar_test.h
    Axon_common/state_test.cpp 
    Axon_common/state_test.h
    Axon_common/statemachine_test.cpp 
    Axon_common/statemachine_test.h
    Axon_common/threading/thread_handler_test.cpp 
    Axon_common/threading/thread_handler_test.h
    main.cpp
)

target_include_directories(Axon_common_unit_tests PRIVATE
    ../../include/
    ../../src/
)

target_link_libraries(Axon_common_unit_tests PRIVATE
    Axon_common
)

