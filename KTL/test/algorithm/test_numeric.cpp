#include "algorithm/algorithm.h"
#include "catch.hpp"
#include "functional/functional.h"
#include "sequence/vector.h"

using namespace ktl;

TEST_CASE("numeric", "[algo]") {
    vector<int> v{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector<int> v1{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    REQUIRE(accumulate(v.begin(), v.end(), 0) == 45);
    REQUIRE(accumulate(v.begin(), v.end(), 0, minus<int>()) == -45);
    REQUIRE(inner_product(v.begin(), v.end(), v1.begin(), 0) == 285);
    REQUIRE(inner_product(v.begin(), v.end(), v1.begin(), 0, minus<int>(), plus<int>()) == -90);
}

TEST_CASE("adjacent_difference", "[algo]") {
    vector<int> v{1, 2, 3, 4, 5};
    vector<int> result(5, 0);

    adjacent_difference(v.begin(), v.end(), result.begin());

    for (int i = 0; i < 5; i++) {
        REQUIRE(result[i] == 1);
    }

    adjacent_difference(v.begin(), v.end(), result.begin(), plus<int>());

    for (int i = 0; i < 5; i++) {
        REQUIRE(result[i] == (2 * i + 1));
    }
}

TEST_CASE("iota", "[algo]") {
    vector<int> v(5, 0);

    iota(v.begin(), v.end(), 0);

    for (int i = 0; i < 5; i++) {
        REQUIRE(v[i] == i);
    }
}
