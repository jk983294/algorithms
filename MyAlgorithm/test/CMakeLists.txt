SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../")

set(tests
        main.cpp
        math/TestMaxSumSubVector.cpp
        math/TestPostfixExpression.cpp
        brutal_force/TestAddFactor.cpp
        data_structure/TestHashTable.cpp
        data_structure/TestSet.cpp
        data_structure/TestSort.cpp
        data_structure/tree/TestBinaryTree.cpp
        data_structure/tree/TestBinarySearchTree.cpp
        data_structure/tree/TestLeftist.cpp
        data_structure/tree/TestRedBlackTree.cpp
        data_structure/heap/TestMinHeap.cpp
        data_structure/heap/TestMaxHeap.cpp
        data_structure/heap/TestBinomialHeap.cpp
        data_structure/heap/TestDeap.cpp
        data_structure/heap/TestFibonacciHeap.cpp
        data_structure/graph/TestDag.cpp
        data_structure/graph/TestDenseGraph.cpp
        data_structure/graph/TestSparseGraph.cpp
        data_structure/graph/TestKruskal.cpp
        data_structure/graph/TestPrim.cpp
        heuristic/TestAStar.cpp
        dynamic_programming/TestEggDropPuzzle.cpp
        dynamic_programming/TestLongestCommonString.cpp
        dynamic_programming/TestMatrixMultiple.cpp
        dynamic_programming/TestViterbi.cpp
        string/TestKmp.cpp
        string/TestTrieTree.cpp
        pattern/disruptor/TestRingBuffer.cpp
        pattern/disruptor/TestSequence.cpp
        pattern/disruptor/TestClaimStrategy.cpp
        pattern/disruptor/TestWaitStrategy.cpp
        pattern/disruptor/TestSequenceBarrier.cpp
        pattern/disruptor/TestSequencer.cpp
        )

enable_testing()

add_executable(test.algo ${tests})
target_link_libraries(test.algo AlgoModule)
target_link_libraries(test.algo pthread)

install(FILES heuristic/AStarMap.txt DESTINATION /var/tmp/test/)
install(FILES heuristic/AStarMap1.txt DESTINATION /var/tmp/test/)
install(FILES heuristic/ViterbiConf.txt DESTINATION /var/tmp/test/)
