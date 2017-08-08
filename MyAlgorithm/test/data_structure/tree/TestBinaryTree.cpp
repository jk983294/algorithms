#include "catch.hpp"
#include "data_structure/tree/BinaryTree.h"

TEST_CASE("BinaryTree", "[BinaryTree]") {
    BinaryTree<int> bt;
    bt.set_root(3);
    bt.insert(3, 5, true);
    bt.insert(5, 4, false);
    bt.insert(3, 1, false);
    bt.insert(1, -1, false);
    bt.insert(1, 2, true);

    bt.in_order();
    REQUIRE(vector<int>({-1, 1, 2, 3, 4, 5}) == bt.iterateResult);

    bt.pre_order();
    REQUIRE(vector<int>({3, 1, -1, 2, 5, 4}) == bt.iterateResult);

    bt.post_order();
    REQUIRE(vector<int>({-1, 2, 1, 4, 5, 3}) == bt.iterateResult);

    bt.level_order();
    REQUIRE(vector<int>({3, 1, 5, -1, 2, 4}) == bt.iterateResult);

    REQUIRE(vector<int>({3, 1}) == bt.find_path(1));

    REQUIRE(vector<int>({-1, 1, 2}) == bt.nearestAncestor(-1, 2));
}
