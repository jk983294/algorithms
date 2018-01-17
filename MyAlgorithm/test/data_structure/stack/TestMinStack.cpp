#include "catch.hpp"
#include "data_structure/stack/MinStack.h"

TEST_CASE("MinStack", "[MinStack]") {
    MinStack ms;
    ms.push(3);
    ms.push(4);
    ms.push(5);
    ms.push(1);
    ms.push(2);
    ms.push(1);

    REQUIRE(ms.get_min() == 1);
    ms.pop();
    REQUIRE(ms.get_min() == 1);
    ms.pop();
    REQUIRE(ms.get_min() == 1);
    ms.pop();
    REQUIRE(ms.get_min() == 3);
    ms.pop();
    REQUIRE(ms.get_min() == 3);
    ms.pop();
    REQUIRE(ms.get_min() == 3);
    ms.pop();

    REQUIRE(ms.empty());
}
