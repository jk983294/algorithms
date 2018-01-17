#include "catch.hpp"
#include "math/MaxSubMatrix.h"

TEST_CASE("MaxSubMatrix", "[MaxSubMatrix]") {
    vector<vector<int>> matrix{{1, 0, 1, 1}, {1, 1, 1, 1}, {1, 1, 1, 0}};
    MaxSubMatrix msm;
    REQUIRE(msm.process(matrix) == 6);
}
