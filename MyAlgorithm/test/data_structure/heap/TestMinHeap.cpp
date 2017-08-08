#include "catch.hpp"
#include "data_structure/heap/MinHeap.h"

TEST_CASE("MinHeap", "[MinHeap]") {
    MinHeap<int> h;
    int ret, index;
    h.insertKey(9);
    h.insertKey(2);
    h.insertKey(3);
    h.insertKey(7);
    h.insertKey(5);
    h.insertKey(6);

    REQUIRE(vector<int>({2, 5, 3, 9, 7, 6}) == vector<int>(h.heap.begin() + 1, h.heap.begin() + h.size + 1));

    index = h.findItem(3);
    REQUIRE(3 == index);
    h.changeItem(index, 8);

    REQUIRE(vector<int>({2, 5, 6, 9, 7, 8}) == vector<int>(h.heap.begin() + 1, h.heap.begin() + h.size + 1));

    h.deleteKey(ret);
    REQUIRE(vector<int>({5, 7, 6, 9, 8}) == vector<int>(h.heap.begin() + 1, h.heap.begin() + h.size + 1));
    h.deleteKey(ret);
    REQUIRE(vector<int>({6, 7, 8, 9}) == vector<int>(h.heap.begin() + 1, h.heap.begin() + h.size + 1));
    h.deleteKey(ret);
    h.deleteKey(ret);
    h.deleteKey(ret);
    h.deleteKey(ret);
    h.deleteKey(ret);
    REQUIRE(0 == h.size);
}
