#include "catch.hpp"
#include "data_structure/SortAlgorithm.h"

static vector<int> expected{1, 5, 11, 15, 19, 26, 37, 48, 59, 61};

TEST_CASE("InsertSort", "[Sort]") {
    int data[] = {26, 5, 37, 1, 61, 11, 59, 15, 48, 19};
    int n = sizeof(data) / sizeof(int);
    SortAlgorithm<int> sa(data, n);
    sa.insertSort();

    for (size_t i = 0; i < expected.size(); ++i) {
        REQUIRE(expected[i] == data[i]);
    }
}

TEST_CASE("ShellSort", "[Sort]") {
    int data[] = {26, 5, 37, 1, 61, 11, 59, 15, 48, 19};
    int n = sizeof(data) / sizeof(int);
    SortAlgorithm<int> sa(data, n);
    sa.shellSort();

    for (size_t i = 0; i < expected.size(); ++i) {
        REQUIRE(expected[i] == data[i]);
    }
}

TEST_CASE("QuickSort", "[Sort]") {
    int data[] = {26, 5, 37, 1, 61, 11, 59, 15, 48, 19};
    int n = sizeof(data) / sizeof(int);
    SortAlgorithm<int> sa(data, n);
    sa.quickSort(0, n - 1);

    for (size_t i = 0; i < expected.size(); ++i) {
        REQUIRE(expected[i] == data[i]);
    }
}

TEST_CASE("BubbleSort", "[Sort]") {
    int data[] = {26, 5, 37, 1, 61, 11, 59, 15, 48, 19};
    int n = sizeof(data) / sizeof(int);
    SortAlgorithm<int> sa(data, n);
    sa.bubbleSort();

    for (size_t i = 0; i < expected.size(); ++i) {
        REQUIRE(expected[i] == data[i]);
    }
}

TEST_CASE("HeapSort", "[Sort]") {
    int data[] = {26, 5, 37, 1, 61, 11, 59, 15, 48, 19};
    int n = sizeof(data) / sizeof(int);
    SortAlgorithm<int> sa(data, n);
    sa.heapSort();

    for (size_t i = 0; i < expected.size(); ++i) {
        REQUIRE(expected[i] == data[i]);
    }
}

TEST_CASE("binarySearch", "[Sort]") {
    int data[] = {1, 5, 11, 15, 19, 26, 37, 48, 59, 61};
    int n = sizeof(data) / sizeof(int);
    SortAlgorithm<int> sa(data, n);
    REQUIRE(sa.binarySearch(26));
    REQUIRE(!sa.binarySearch(25));

    REQUIRE(sa.binarySearchForIndex(26) == 5);
    REQUIRE(sa.binarySearchForIndex(64) == -1);
}
