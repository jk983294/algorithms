#include "catch.hpp"
#include "dynamic_programming/LongestCommonString.h"

TEST_CASE("LongestCommonString test1", "[LongestCommonString1]") {
    //算法导论例子
    LCS lcs;
    lcs.x = "abcbdab";
    lcs.y = "bdcaba";
    REQUIRE(4 == lcs.lcs_length());
    lcs.find_all_lcs();
    REQUIRE(set<string>({"bcab", "bcba", "bdab"}) == lcs.results);
}

TEST_CASE("LongestCommonString test2", "[LongestCommonString2]") {
    // 金远平书例子
    LCS lcs;
    lcs.x = "abdebcbb";
    lcs.y = "adacbcb";
    REQUIRE(5 == lcs.lcs_length());
    lcs.find_all_lcs();
    REQUIRE(set<string>({"adbcb", "adcbb"}) == lcs.results);
}
