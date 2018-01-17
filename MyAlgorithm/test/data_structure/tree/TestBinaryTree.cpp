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

    bt.dfs_in_order();
    REQUIRE(vector<int>({-1, 1, 2, 3, 4, 5}) == bt.iterateResult);

    bt.pre_order();
    REQUIRE(vector<int>({3, 1, -1, 2, 5, 4}) == bt.iterateResult);

    bt.dfs_pre_order();
    REQUIRE(vector<int>({3, 1, -1, 2, 5, 4}) == bt.iterateResult);

    bt.post_order();
    REQUIRE(vector<int>({-1, 2, 1, 4, 5, 3}) == bt.iterateResult);

    bt.dfs_post_order();
    REQUIRE(vector<int>({-1, 2, 1, 4, 5, 3}) == bt.iterateResult);

    bt.dfs();
    REQUIRE(vector<int>({3, 1, -1, 2, 5, 4}) == bt.iterateResult);

    bt.dfs_without_visited_flag();
    REQUIRE(vector<int>({3, 1, -1, 2, 5, 4}) == bt.iterateResult);

    bt.level_order();
    REQUIRE(vector<int>({3, 1, 5, -1, 2, 4}) == bt.iterateResult);

    REQUIRE(vector<int>({3, 1}) == bt.find_path(1));

    REQUIRE(vector<int>({-1, 1, 2}) == bt.nearestAncestor(-1, 2));
}

TEST_CASE("max_sub_bst", "[max_sub_bst]") {
    BinaryTree<int> bt;
    bt.set_root(6);
    bt.insert(6, 12, true);
    bt.insert(6, 1, false);
    bt.insert(1, 3, true);
    bt.insert(1, 0, false);
    bt.insert(12, 13, true);
    bt.insert(12, 10, false);
    bt.insert(10, 14, true);
    bt.insert(10, 4, false);
    bt.insert(14, 15, true);
    bt.insert(14, 11, false);
    bt.insert(4, 5, true);
    bt.insert(4, 2, false);
    bt.insert(13, 16, true);
    bt.insert(13, 20, false);

    REQUIRE(bt.max_sub_bst()->data == 10);
}
