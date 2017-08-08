#include "catch.hpp"
#include "data_structure/heap/MaxHeap.h"

TEST_CASE("MaxHeap", "[MaxHeap]") {
    MaxHeap<int> h;
    int ret;
    h.insertKey(2);
    h.insertKey(3);
    h.insertKey(7);
    h.insertKey(5);
    h.insertKey(6);
    h.insertKey(9);
    REQUIRE(vector<int>({9, 6, 7, 2, 5, 3}) == vector<int>(h.heap.begin() + 1, h.heap.begin() + h.size + 1));

    h.deleteKey(ret);
    h.deleteKey(ret);
    h.deleteKey(ret);
    REQUIRE(vector<int>({5, 2, 3}) == vector<int>(h.heap.begin() + 1, h.heap.begin() + h.size + 1));
    h.deleteKey(ret);
    h.deleteKey(ret);
    h.deleteKey(ret);
    h.deleteKey(ret);
    REQUIRE(0 == h.size);
}
