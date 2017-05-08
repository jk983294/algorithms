#include "catch.hpp"
#include "sequence/list.h"

using namespace ktl;

TEST_CASE("ops be used in list", "[list]") {
    list<int> l{1, 2, 3, 4, 5, 6, 7, 8, 9};

    l.push_front(0);
    l.push_back(10);
    REQUIRE(l.front() == 0);
    REQUIRE(l.back() == 10);

    l.pop_front();
    l.pop_back();
    REQUIRE(l.front() == 1);
    REQUIRE(l.back() == 9);

    l.splice(l.begin(), l.begin() + 3, l.end());
    REQUIRE(l.front() == 4);

    l.insert(l.end(), 42);
    REQUIRE(l.back() == 42);

    l.erase(l.begin());
    REQUIRE(l.size() == 9);

    l.clear();
    REQUIRE(l.size() == 0);
}

TEST_CASE("init list", "[list]") {
    list<int> l{1, 2, 3, 4, 5, 6};
    REQUIRE(l.size() == 6);
}

TEST_CASE("list for loop", "[list]") {
    list<int> l{42, 42, 42};

    for (list<int>::iterator i = l.begin(); i != l.end(); ++i) {
        REQUIRE(*i == 42);
    }
}

TEST_CASE("list sort", "[list]") {
    list<int> l{3, 1, 2, 9, 0, 4, 7, 5, 6, 8};
    l.sort();

    list<int>::iterator itr = l.begin();
    for (int i = 0; i < 10; i++) {
        REQUIRE(*itr == i);
        itr++;
    }
}
