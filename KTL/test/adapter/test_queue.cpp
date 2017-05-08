#include "adapter/queue.h"
#include "catch.hpp"
#include "sequence/list.h"

using namespace ktl;

TEST_CASE("ops be used in queue", "[queue]") {
    queue<int> q;
    REQUIRE(q.size() == 0);

    q.push(1);
    q.push(2);
    REQUIRE(q.size() == 2);
    REQUIRE(q.front() == 1);
    REQUIRE(q.back() == 2);

    q.pop();
    REQUIRE(q.size() == 1);
    REQUIRE(q.front() == 2);
    REQUIRE(q.back() == 2);

    q.clear();
    REQUIRE(q.size() == 0);
}

TEST_CASE("queue with list as underline container", "[queue]") {
    queue<int, list<int> > q;
    REQUIRE(q.size() == 0);

    q.push(1);
    q.push(2);
    REQUIRE(q.size() == 2);
    REQUIRE(q.front() == 1);
    REQUIRE(q.back() == 2);

    q.pop();
    REQUIRE(q.size() == 1);
    REQUIRE(q.front() == 2);
    REQUIRE(q.back() == 2);

    q.clear();
    REQUIRE(q.size() == 0);
}
