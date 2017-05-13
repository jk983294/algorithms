#include "catch.hpp"
#include "functional/functional.h"

using namespace ktl;

TEST_CASE("math", "[functional]") {
    plus<int> plusObj;
    minus<int> minusObj;
    multiply<int> multiplyObj;
    divide<int> divideObj;
    module<int> moduleObj;
    negate<int> negateObj;

    REQUIRE(plusObj(1, 2) == 3);
    REQUIRE(minusObj(1, 2) == -1);
    REQUIRE(multiplyObj(1, 2) == 2);
    REQUIRE(divideObj(2, 1) == 2);
    REQUIRE(moduleObj(1, 2) == 1);
    REQUIRE(negateObj(1) == -1);
}
