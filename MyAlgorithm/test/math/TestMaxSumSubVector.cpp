#include "catch.hpp"
#include "math/MaxSumSubVector.h"

TEST_CASE("MaxSumSubVector", "[MaxSumSubVector]") {
    vector<int> a{-6, 2, 4, -7, 5, 0, 2, -1, 6, -9, 10, -2};
    int start, end;
    int result = calculateMaxSum(a, start, end);
    REQUIRE(result == 13);
    REQUIRE(start == 4);
    REQUIRE(end == 10);

    result = calculateMaxMultiply(a, start, end);
    REQUIRE(result == 1680);
    REQUIRE(start == 0);
    REQUIRE(end == 4);

    vector<int> b{-2, 11, -4, 13, -5, -2};
    result = calculateMaxSum(b, start, end);
    REQUIRE(result == 20);
    REQUIRE(start == 1);
    REQUIRE(end == 3);

    result = calculateMaxMultiply(b, start, end);
    REQUIRE(result == 11440);
    REQUIRE(start == 0);
    REQUIRE(end == 5);
}
