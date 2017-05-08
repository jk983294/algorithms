#include "catch.hpp"
#include "sequence/vector.h"

using namespace ktl;

TEST_CASE("ops be used in vector", "[vector]") {
    vector<int> v(2, 9);
    REQUIRE(v.size() == 2);
    REQUIRE(v.capacity() == 2);

    v.push_back(1);
    REQUIRE(v.size() == 3);
    REQUIRE(v.capacity() == 4);

    v.push_back(2);
    REQUIRE(v.size() == 4);
    REQUIRE(v.capacity() == 4);

    v.push_back(3);
    REQUIRE(v.size() == 5);
    REQUIRE(v.capacity() == 8);

    v.insert(v.begin(), 4, 42);
    REQUIRE(v.size() == 9);
    REQUIRE(v.capacity() == 10);

    v.erase(v.begin());
    REQUIRE(v.size() == 8);
    REQUIRE(v.capacity() == 10);

    v.clear();
    REQUIRE(v.size() == 0);
    REQUIRE(v.capacity() == 10);
}

TEST_CASE("vector init with init list", "[vector]") {
    vector<int> v{1, 2, 3, 4, 5, 6};
    REQUIRE(v.size() == 6);
    REQUIRE(v.capacity() == 6);
}

TEST_CASE("vector for loop", "[vector]") {
    vector<int> v;
    v.insert(v.begin(), 10, 42);

    for (size_t i = 0; i < 10; i++) {
        REQUIRE(v[i] == 42);
    }

    for (vector<int>::iterator i = v.begin(); i != v.end(); ++i) {
        REQUIRE(*i == 42);
    }
}
