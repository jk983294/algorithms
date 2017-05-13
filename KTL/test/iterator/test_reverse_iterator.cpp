
#include "algorithm/algorithm.h"
#include "catch.hpp"
#include "iterator/insert_iterator.h"
#include "sequence/deque.h"
#include "sequence/vector.h"
#include "util/display.h"

using namespace ktl;

TEST_CASE("vector reverse iterator", "[reverse_iterator]") {
    vector<int> v{0, 1, 2, 3, 4};

    int index = 4;
    for (auto i = v.rbegin(); i != v.rend(); ++i) {
        REQUIRE(*i == index--);
    }
}
