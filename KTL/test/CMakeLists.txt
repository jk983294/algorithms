SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../")

set(tests
    main.cpp
    sequence/test_vector.cpp
    sequence/test_list.cpp
    sequence/test_deque.cpp
    adapter/test_stack.cpp
    adapter/test_queue.cpp
    algorithm/test_heap.cpp
    algorithm/test_numeric.cpp
    adapter/test_priority_queue.cpp
    associative/test_rbtree.cpp
    associative/test_set.cpp
    associative/test_map.cpp
    functional/test_functional.cpp
    iterator/test_insert_iterator.cpp
    iterator/test_reverse_iterator.cpp
)

enable_testing()

add_executable(test.ktl ${tests})
target_link_libraries(test.ktl KtlModule)
