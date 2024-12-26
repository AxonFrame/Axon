add_executable(Axon_common_memory_leak_tests
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
    Axon_common/items/table_item_test.cpp
    Axon_common/items/table_item_test.h
    Axon_common/state_test.cpp
    Axon_common/state_test.h
    Axon_common/statemachine_test.cpp
    Axon_common/statemachine_test.h
    Axon_common/threading/bogus_event.cpp
    Axon_common/threading/bogus_event.h
    Axon_common/threading/bogus_thread.cpp
    Axon_common/threading/bogus_thread.h
    Axon_common/threading/thread_test.cpp
    Axon_common/threading/thread_test.h
    main.cpp
)

target_include_directories(Axon_common_memory_leak_tests PRIVATE
    include/
    src/
)

target_link_libraries(Axon_common_memory_leak_tests PRIVATE
    Axon_common
)
