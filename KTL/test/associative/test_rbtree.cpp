#include "associative/rbtree.h"
#include "catch.hpp"
#include "functional/functional.h"
#include "sequence/vector.h"

using namespace ktl;

TEST_CASE("ops be used in rbtree", "[rbtree]") {
    vector<int> v{9, 0, 3, 7, 2, 1, 5, 4, 6, 8};
    rb_tree<int, int, identity<int>, less<int> > tree;
    REQUIRE(tree.size() == 0);

    tree.insert_unique(v.begin(), v.end());

    for (int i = 0; i < 10; i++) {
        auto result = tree.insert_unique(v[i]);
        REQUIRE(result.second == false);
    }

    auto itr = tree.begin();
    for (int i = 0; i < 10; i++) {
        REQUIRE(*itr == i);
        ++itr;
    }
}
