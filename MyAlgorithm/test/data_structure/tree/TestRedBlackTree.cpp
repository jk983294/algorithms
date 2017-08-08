#include "catch.hpp"
#include "data_structure/tree/RedBlackTree.h"

TEST_CASE("RedBlackTree", "[RedBlackTree]") {
    // 例子来源： http://blog.csdn.net/v_JULY_v/article/details/6284050
    RBTree<int> tree;
    // insert 12 1 9 2 0 11 7 19 4 15 18 5 14 13 10 16 6 3 8 17
    tree.Insert(12);
    tree.Insert(1);
    tree.Insert(9);
    tree.Insert(2);
    tree.Insert(0);
    tree.Insert(11);
    tree.Insert(7);
    tree.Insert(19);
    tree.Insert(4);
    tree.Insert(15);
    tree.Insert(18);
    tree.Insert(5);
    tree.Insert(14);
    tree.Insert(13);
    tree.Insert(10);
    tree.Insert(16);
    tree.Insert(6);
    tree.Insert(3);
    tree.Insert(8);
    tree.Insert(17);
    REQUIRE(vector<int>({9, 4, 14, 1, 6, 12, 18, 0, 2, 5, 7, 11, 13, 16, 19, 3, 8, 10, 15, 17}) == tree.level_order());

    tree.Delete(12);
    tree.Delete(1);
    tree.Delete(9);
    tree.Delete(2);
    REQUIRE(vector<int>({10, 4, 14, 3, 6, 11, 18, 0, 5, 7, 13, 16, 19, 8, 15, 17}) == tree.level_order());
    tree.Delete(0);
    tree.Delete(11);
    tree.Delete(7);
    tree.Delete(19);
    REQUIRE(vector<int>({10, 4, 14, 3, 6, 13, 16, 5, 8, 15, 18, 17}) == tree.level_order());
    tree.Delete(4);
    tree.Delete(15);
    tree.Delete(18);
    tree.Delete(5);
    REQUIRE(vector<int>({10, 6, 14, 3, 8, 13, 17, 16}) == tree.level_order());
    tree.Delete(14);
    tree.Delete(13);
    tree.Delete(10);
    tree.Delete(16);
    REQUIRE(vector<int>({6, 3, 17, 8}) == tree.level_order());
    tree.Delete(6);
    tree.Delete(3);
    tree.Delete(8);
    tree.Delete(17);
    REQUIRE(vector<int>() == tree.level_order());
}
