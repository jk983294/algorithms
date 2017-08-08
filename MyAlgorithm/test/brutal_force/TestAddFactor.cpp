#include "brutal_force/AddFactor.h"
#include "catch.hpp"

TEST_CASE("AddFactor", "[AddFactor]") {
    vector<set<int>> expected{{1, 7}, {1, 2, 5}, {1, 3, 4}, {2, 6}, {3, 5}};
    vector<set<int>> result = divideToSub(8);
    REQUIRE(expected == result);
}
