cmake_minimum_required(VERSION 3.16)
project(Axon_common VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(Axon_common STATIC
    include/Axon_common/defines.h
    include/Axon_common/uuid.h
    include/Axon_common/enums.h
    include/Axon_common/buffer/bit_buffer.h
    include/Axon_common/buffer/data_buffer.h
    include/Axon_common/buffer/item_buffer.h
    include/Axon_common/buffer/ring_buffer.h
    include/Axon_common/buffer/stack_buffer.h
    include/Axon_common/buffer/stack_buffer_reserve.h
    include/Axon_common/files/binary_file.h
    include/Axon_common/files/binary_file_direct.h
    include/Axon_common/files/text_file.h
    include/Axon_common/items/table_item.h
    include/Axon_common/logger.h
    include/Axon_common/memory_counter.h
    include/Axon_common/functions/file_functions.h
    include/Axon_common/functions/string_functions.h
    include/Axon_common/functions/vector_functions.h
    include/Axon_common/functions/time_functions.h
    include/Axon_common/process_execution.h
    include/Axon_common/progress_bar.h
    include/Axon_common/statemachine.h
    include/Axon_common/structs.h
    include/Axon_common/test_helper/compare_test_helper.h
    include/Axon_common/test_helper/memory_leak_test_helper.h
    include/Axon_common/test_helper/speed_test_helper.h
    include/Axon_common/threading/barrier.h
    include/Axon_common/threading/cleanup_thread.h
    include/Axon_common/threading/event.h
    include/Axon_common/threading/event_queue.h
    include/Axon_common/threading/thread.h
    include/Axon_common/threading/thread_handler.h
    include/Axon_common/upload_file_handle.h
    src/buffer/stack_buffer_reserve.cpp
    src/files/binary_file.cpp
    src/files/binary_file_direct.cpp
    src/files/text_file.cpp
    src/items/table_item.cpp
    src/logger.cpp
    src/memory_counter.cpp
    src/functions/file_functions.cpp
    src/functions/string_functions.cpp
    src/functions/vector_functions.cpp
    src/process_execution.cpp
    src/progress_bar.cpp
    src/state.h
    src/statemachine.cpp
    src/test_helper/compare_test_helper.cpp
    src/test_helper/memory_leak_test_helper.cpp
    src/test_helper/speed_test_helper.cpp
    src/threading/barrier.cpp
    src/threading/cleanup_thread.cpp
    src/threading/event.cpp
    src/threading/event_queue.cpp
    src/threading/thread.cpp
    src/threading/thread_handler.cpp
    src/uuid.cpp
)

include_directories(
    include/
    src/
)

if(run_tests)
    add_subdirectory(tests)
endif()
