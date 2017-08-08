#include "catch.hpp"
#include "data_structure/tree/BinarySearchTree.h"

TEST_CASE("BinarySearchTree", "[BinarySearchTree]") {
    BinarySearchTree<int> bst;
    bst.insert(3);
    bst.insert(5);
    bst.insert(4);
    bst.insert(1);
    bst.insert(-1);
    bst.insert(2);

    bst.in_order();
    REQUIRE(vector<int>({-1, 1, 2, 3, 4, 5}) == bst.iterateResult);

    bst.pre_order();
    REQUIRE(vector<int>({3, 1, -1, 2, 5, 4}) == bst.iterateResult);

    bst.post_order();
    REQUIRE(vector<int>({-1, 2, 1, 4, 5, 3}) == bst.iterateResult);

    bst.level_order();
    REQUIRE(vector<int>({3, 1, 5, -1, 2, 4}) == bst.iterateResult);

    REQUIRE(nullptr != bst.search(1));

    REQUIRE(bst.deleteKey(1));

    bst.level_order();
    REQUIRE(vector<int>({3, -1, 5, 2, 4}) == bst.iterateResult);
}
