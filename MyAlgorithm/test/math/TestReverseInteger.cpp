#include "catch.hpp"
#include "math/ReverseInteger.h"

TEST_CASE("ReverseInteger", "[ReverseInteger]") {
    ReverseInteger ri;
    REQUIRE(ri.reverse(123) == 321);
    REQUIRE(ri.reverse(-123) == -321);
    REQUIRE(ri.reverse(120) == 21);
}
