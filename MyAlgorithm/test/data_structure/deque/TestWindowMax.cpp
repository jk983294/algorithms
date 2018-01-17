#include "catch.hpp"
#include "data_structure/deque/WindowMax.h"

TEST_CASE("WindowMax", "[WindowMax]") {
    WindowMax wm;

    REQUIRE(wm.get_window_max_array({4, 3, 5, 4, 3, 3, 6, 7}, 3) == vector<int>({4, 4, 5, 5, 5, 4, 6, 7}));
}
