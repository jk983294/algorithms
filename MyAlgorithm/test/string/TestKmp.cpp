#include "catch.hpp"
#include "string/KMP.h"

TEST_CASE("KMP", "[KMP]") {
    KMP kmp;
    kmp.str = "fksabcabcacabdjf";
    kmp.pattern = "abcabcacab";
    int pos = kmp.kmp();
    REQUIRE(pos == 3);

    vector<int> expectedFail{-1, -1, -1, 0, 1, 2, 3, -1, 0, 1};
    REQUIRE(expectedFail == kmp.f);
}
