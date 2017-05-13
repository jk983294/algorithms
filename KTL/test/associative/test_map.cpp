#include "associative/map.h"
#include "catch.hpp"
#include "sequence/vector.h"

using namespace ktl;

TEST_CASE("ops be used in map", "[map]") {
    vector<int> v{9, 0, 3, 7, 2, 1, 5, 4, 6, 8, 9, 0, 3, 7, 2, 1, 5, 4, 6, 8};
    map<int, int> m;
    REQUIRE(m.size() == 0);

    for (auto i = v.begin(); i < v.end(); ++i) {
        m[*i] = *i;
    }

    auto itr = m.begin();
    for (int i = 0; i < 10; i++) {
        REQUIRE(m[i] == i);
        ++itr;
    }
}
