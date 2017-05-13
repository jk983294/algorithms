#include "algorithm/algorithm.h"
#include "catch.hpp"
#include "iterator/insert_iterator.h"
#include "sequence/deque.h"
#include "sequence/vector.h"
#include "util/display.h"

using namespace ktl;

TEST_CASE("front", "[insert_iterator]") {
    vector<int> v{0, 1, 2, 3, 4};
    deque<int> dq;

    copy(v.begin(), v.end(), front_inserter(dq));

    for (int i = 0; i < 5; i++) {
        REQUIRE(dq[i] == (4 - i));
    }
}

TEST_CASE("back", "[insert_iterator]") {
    vector<int> v{0, 1, 2, 3, 4};
    vector<int> x;

    copy(v.begin(), v.end(), back_inserter(x));

    for (int i = 0; i < 5; i++) {
        REQUIRE(x[i] == i);
    }
}
