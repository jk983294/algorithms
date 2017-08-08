#include "catch.hpp"
#include "dynamic_programming/MatrixMultiple.h"

TEST_CASE("MatrixMultiple", "[MatrixMultiple]") {
    MatrixMultiple mm;
    mm.set({30, 35, 15, 5, 10, 20}, {35, 15, 5, 10, 20, 25});

    REQUIRE(15125 == mm.multiple());
}
