#include "catch.hpp"
#include "sequence/deque.h"

using namespace ktl;

TEST_CASE("ops be used in deque", "[deque]") {
    deque<int> d(2, 9);
    REQUIRE(d.size() == 2);

    d.push_back(1);
    REQUIRE(d.size() == 3);
    REQUIRE(d.back() == 1);

    d.push_front(2);
    REQUIRE(d.size() == 4);
    REQUIRE(d.front() == 2);

    d.insert(d.begin() + 2, 42);
    REQUIRE(d.size() == 5);
    REQUIRE(*(d.begin() + 2) == 42);

    d.erase(d.begin() + 2);
    REQUIRE(d.size() == 4);
    REQUIRE(*(d.begin() + 2) == 9);

    d.clear();
    REQUIRE(d.size() == 0);
}

TEST_CASE("deque for loop", "[deque]") {
    deque<int> dp(3, 42);

    for (auto i = dp.begin(); i != dp.end(); ++i) {
        REQUIRE(*i == 42);
    }
}
