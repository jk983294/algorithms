#include "catch.hpp"
#include "data_structure/heap/BinomialHeap.h"

TEST_CASE("BinomialHeap", "[BinomialHeap]") {
    MinBinomialHeap<int> h;
    h.clear();
    REQUIRE(0 == h.size);

    int ret;
    h.insertKey(9);
    h.insertKey(2);
    h.insertKey(3);
    h.insertKey(7);
    h.insertKey(5);
    h.insertKey(6);

    REQUIRE(h.deleteKey(9));
    h.deleteMin(ret);
    REQUIRE(2 == ret);
    h.deleteMin(ret);
    REQUIRE(3 == ret);
    h.deleteMin(ret);
    REQUIRE(5 == ret);

    h.insertKey(9);
    h.insertKey(2);
    h.insertKey(3);

    h.clear();
    REQUIRE(0 == h.size);

    h.insertKey(7);
    h.insertKey(5);
    h.insertKey(6);
    REQUIRE(3 == h.size);
}
