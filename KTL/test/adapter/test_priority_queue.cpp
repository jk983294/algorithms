#include "adapter/priority_queue.h"
#include "catch.hpp"
#include "sequence/vector.h"
#include "util/display.h"

using namespace ktl;

TEST_CASE("ops be used in priority_queue", "[priority_queue]") {
    vector<int> v{9, 0, 3, 7, 2, 1, 5, 4, 6, 8};
    priority_queue<int> pq(v.begin(), v.end());

    for (int i = 0; i < 10; i++) {
        REQUIRE(pq.top() == (9 - i));
        pq.pop();
    }
}

TEST_CASE("push priority_queue", "[priority_queue]") {
    vector<int> v{9, 0, 3, 7, 2, 1, 5, 4, 6, 8};
    priority_queue<int> pq;

    for (int i = 0; i < 10; i++) {
        pq.push(v[i]);
    }

    for (int i = 0; i < 10; i++) {
        REQUIRE(pq.top() == (9 - i));
        pq.pop();
    }
}
