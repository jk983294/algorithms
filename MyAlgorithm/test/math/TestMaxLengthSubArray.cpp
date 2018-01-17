#include "catch.hpp"
#include "math/MaxLengthSubArray.h"

TEST_CASE("MaxLengthSubArray", "[MaxLengthSubArray]") {
    vector<int> v{2, 0, -2, 3, 0, 3, -3, 0};
    MaxLengthSubArray maxLengthSubArray;
    REQUIRE(maxLengthSubArray.process(v, 3) == 8);
    REQUIRE(maxLengthSubArray.process(v, 0) == 4);
}
