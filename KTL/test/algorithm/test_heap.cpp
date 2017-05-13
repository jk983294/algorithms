#include "algorithm/algorithm.h"
#include "catch.hpp"
#include "sequence/vector.h"

using namespace ktl;

TEST_CASE("ops be used in heap", "[heap]") {
    vector<int> result{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector<int> v{9, 0, 3, 7, 2, 1, 5, 4, 6, 8};

    make_heap(v.begin(), v.end());
    heap_sort(v.begin(), v.end());
    for (int i = 0; i < 10; i++) {
        REQUIRE(v[i] == i);
    }
}
