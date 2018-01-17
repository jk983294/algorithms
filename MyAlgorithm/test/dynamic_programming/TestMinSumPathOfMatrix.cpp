#include "catch.hpp"
#include "dynamic_programming/MinSumPathOfMatrix.h"

TEST_CASE("MinSumPathOfMatrix", "[MinSumPathOfMatrix]") {
    MinSumPath msp;
    vector<vector<int>> matrix{{1, 3, 5, 9}, {8, 1, 3, 4}, {5, 0, 6, 1}, {8, 8, 4, 0}};
    REQUIRE(12 == msp.process(matrix));
}
