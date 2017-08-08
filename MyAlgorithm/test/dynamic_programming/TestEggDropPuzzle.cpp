#include "catch.hpp"
#include "dynamic_programming/EggDropPuzzle.h"

TEST_CASE("EggDropPuzzle", "[EggDropPuzzle]") {
    EggDropPuzzle edp;
    edp.eggcount = 2;
    edp.height = 32;
    edp.calculate_cost();
    // edp.print_cost();
    REQUIRE(8 == edp.cost[2][32]);
}
