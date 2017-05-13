#include "associative/set.h"
#include "catch.hpp"
#include "sequence/vector.h"

using namespace ktl;

TEST_CASE("ops be used in set", "[set]") {
    vector<int> v{9, 0, 3, 7, 2, 1, 5, 4, 6, 8, 9, 0, 3, 7, 2, 1, 5, 4, 6, 8};
    set<int> s;
    REQUIRE(s.size() == 0);

    s.insert(v.begin(), v.end());

    auto itr = s.begin();
    for (int i = 0; i < 10; i++) {
        REQUIRE(*itr == i);
        ++itr;
    }
}
