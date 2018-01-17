#include "catch.hpp"
#include "data_structure/SingleList.h"

TEST_CASE("SingleList", "[SingleList]") {
    SingleList<int> list;
    for (int i = 0; i < 10; ++i) {
        list.push_front(i);
    }

    list.reverse();
    SingleListNode<int>* itr = list.m_head;
    for (int j = 0; j < 10; ++j) {
        REQUIRE(itr->val == j);
        itr = itr->next;
    }
    itr = nullptr;

    SingleListNode<int>* result = list.remove_last_kth_element(11);
    REQUIRE(result == nullptr);

    result = list.remove_last_kth_element(10);
    REQUIRE(result->val == 0);
    delete result;

    result = list.remove_last_kth_element(3);
    REQUIRE(result->val == 7);
    delete result;
}
