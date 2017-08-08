#include "catch.hpp"
#include "data_structure/heap/FibonacciHeap.h"

TEST_CASE("FibonacciHeap", "[FibonacciHeap]") {
    FibonacciHeap<size_t, string> h;

    h.insert(4, "a");
    h.insert(2, "b");
    h.insert(7, "c");
    h.insert(5, "d");
    h.insert(1, "e");
    h.insert(8, "f");
    // delete all test
    vector<size_t> result;
    while (!h.empty()) {
        result.push_back(h.minimum()->key());
        h.removeMinimum();
    }
    REQUIRE(vector<size_t>({1, 2, 4, 5, 7, 8}) == result);

    //额外记录堆中数据指针，方便查找
    vector<FibonacciHeapNode<size_t, string>*> nodes(6);
    nodes[0] = h.insert(400, "a");
    nodes[1] = h.insert(200, "b");
    nodes[2] = h.insert(70, "c");
    nodes[3] = h.insert(50, "d");
    nodes[4] = h.insert(10, "e");
    nodes[5] = h.insert(80, "f");
    REQUIRE(10 == h.minimum()->key());

    h.removeMinimum();
    REQUIRE(50 == h.minimum()->key());
    nodes[4] = nullptr;

    /// how to decrease key
    for (uint i = 0; i < nodes.size(); ++i) {
        if (!nodes[i])  // minimum - already removed
            continue;
        h.decreaseKey(nodes[i], nodes[i]->key() / 10);
    }

    h.insert(4, "AA");
    h.insert(2, "BB");
    h.insert(7, "CC");

    result.clear();
    while (!h.empty()) {
        result.push_back(h.minimum()->key());
        h.removeMinimum();
    }

    REQUIRE(vector<size_t>({2, 4, 5, 7, 7, 8, 20, 40}) == result);
}
