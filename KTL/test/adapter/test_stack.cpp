#include "adapter/stack.h"
#include "catch.hpp"
#include "sequence/list.h"

using namespace ktl;

TEST_CASE("ops be used in stack", "[stack]") {
    stack<int> s;
    REQUIRE(s.size() == 0);

    s.push(1);
    REQUIRE(s.size() == 1);
    REQUIRE(s.top() == 1);

    s.push(2);
    REQUIRE(s.size() == 2);
    REQUIRE(s.top() == 2);

    s.pop();
    REQUIRE(s.size() == 1);
    REQUIRE(s.top() == 1);

    s.pop();
    REQUIRE(s.size() == 0);

    s.clear();
    REQUIRE(s.size() == 0);
}

TEST_CASE("stack with list as underline container", "[stack]") {
    stack<int, list<int> > s;
    REQUIRE(s.size() == 0);

    s.push(1);
    REQUIRE(s.size() == 1);
    REQUIRE(s.top() == 1);

    s.push(2);
    REQUIRE(s.size() == 2);
    REQUIRE(s.top() == 2);

    s.pop();
    REQUIRE(s.size() == 1);
    REQUIRE(s.top() == 1);

    s.pop();
    REQUIRE(s.size() == 0);

    s.clear();
    REQUIRE(s.size() == 0);
}
