#include "associative/FlatMap.h"
#include "catch.hpp"
#include "sequence/vector.h"

using namespace ktl;

TEST_CASE("ops be used in FlatMap", "[FlatMap]") {
    FlatMap<int, double> map1;

    FlatMap<int, double>::iterator it0 = map1.find(12);
    REQUIRE(it0 == map1.end());
    REQUIRE(map1.count(12) == 0);

    map1.insert(10, 1.);
    map1.insert(10, -999.99);
    map1.insert(11, 100.);
    map1.insert(12, 29.);
    map1.insert(13, 66.);
    map1.insert(14, 44.);
    map1.insert(12, 40.);
    map1.insert(12, 50.);

    REQUIRE(map1.size() == 5);
    REQUIRE(map1.count(12) == 1);

    int nCount = 0;
    {
        for (FlatMap<int, double>::iterator it = map1.begin(); it != map1.end(); it++) {
            nCount++;
        }
    }
    REQUIRE(nCount == 5);

    map1.erase(11);

    REQUIRE(map1.size() == 4);

    FlatMap<int, double>::iterator it2 = map1.find(12);
    REQUIRE(it2 != map1.end());
    REQUIRE(it2->first == 12);
    REQUIRE(it2->second == 50);
}
