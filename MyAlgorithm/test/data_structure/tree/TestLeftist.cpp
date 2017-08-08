#include "catch.hpp"
#include "data_structure/tree/Leftist.h"

TEST_CASE("MinLeftistTree", "[Leftist]") {
    MinLeftistTree<int> mlt;
    mlt.insert(7);
    mlt.level_order();
    REQUIRE(vector<int>({7}) == mlt.iterateResult);
    mlt.insert(13);
    mlt.level_order();
    REQUIRE(vector<int>({7, 13}) == mlt.iterateResult);
    mlt.insert(11);
    mlt.level_order();
    REQUIRE(vector<int>({7, 13, 11}) == mlt.iterateResult);
    mlt.insert(50);
    mlt.level_order();
    REQUIRE(vector<int>({7, 13, 11, 50}) == mlt.iterateResult);
    mlt.insert(80);
    mlt.level_order();
    REQUIRE(vector<int>({7, 11, 13, 50, 80}) == mlt.iterateResult);
    mlt.insert(2);
    mlt.level_order();
    REQUIRE(vector<int>({2, 7, 11, 13, 50, 80}) == mlt.iterateResult);

    int ret;
    mlt.deleteKey(ret);
    mlt.level_order();
    REQUIRE(vector<int>({7, 11, 13, 50, 80}) == mlt.iterateResult);
    mlt.deleteKey(ret);
    mlt.level_order();
    REQUIRE(vector<int>({11, 50, 13, 80}) == mlt.iterateResult);
    mlt.deleteKey(ret);
    mlt.level_order();
    REQUIRE(vector<int>({13, 80, 50}) == mlt.iterateResult);
    mlt.deleteKey(ret);
    mlt.level_order();
    REQUIRE(vector<int>({50, 80}) == mlt.iterateResult);
    mlt.deleteKey(ret);
    mlt.level_order();
    REQUIRE(vector<int>({80}) == mlt.iterateResult);
    mlt.deleteKey(ret);
    mlt.level_order();
    REQUIRE(vector<int>() == mlt.iterateResult);
    mlt.deleteKey(ret);
    mlt.level_order();
    REQUIRE(vector<int>() == mlt.iterateResult);
}

TEST_CASE("MaxLeftistTree", "[Leftist]") {
    MaxLeftistTree<int> mlt;
    mlt.insert(7);
    mlt.level_order();
    REQUIRE(vector<int>({7}) == mlt.iterateResult);
    mlt.insert(13);
    mlt.level_order();
    REQUIRE(vector<int>({13, 7}) == mlt.iterateResult);
    mlt.insert(11);
    mlt.level_order();
    REQUIRE(vector<int>({13, 7, 11}) == mlt.iterateResult);
    mlt.insert(50);
    mlt.level_order();
    REQUIRE(vector<int>({50, 13, 7, 11}) == mlt.iterateResult);
    mlt.insert(80);
    mlt.level_order();
    REQUIRE(vector<int>({80, 50, 13, 7, 11}) == mlt.iterateResult);
    mlt.insert(2);
    mlt.level_order();
    REQUIRE(vector<int>({80, 50, 2, 13, 7, 11}) == mlt.iterateResult);

    int ret;
    mlt.deleteKey(ret);
    mlt.level_order();
    REQUIRE(vector<int>({50, 13, 2, 7, 11}) == mlt.iterateResult);
    mlt.deleteKey(ret);
    mlt.level_order();
    REQUIRE(vector<int>({13, 7, 11, 2}) == mlt.iterateResult);
    mlt.deleteKey(ret);
    mlt.level_order();
    REQUIRE(vector<int>({11, 2, 7}) == mlt.iterateResult);
    mlt.deleteKey(ret);
    mlt.level_order();
    REQUIRE(vector<int>({7, 2}) == mlt.iterateResult);
    mlt.deleteKey(ret);
    mlt.level_order();
    REQUIRE(vector<int>({2}) == mlt.iterateResult);
    mlt.deleteKey(ret);
    mlt.level_order();
    REQUIRE(vector<int>() == mlt.iterateResult);
    mlt.deleteKey(ret);
    mlt.level_order();
    REQUIRE(vector<int>() == mlt.iterateResult);
}
