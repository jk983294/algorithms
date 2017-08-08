#include "catch.hpp"
#include "data_structure/Set.h"

TEST_CASE("Set", "[Set]") {
    MySet<int>* set = new MySet<int>();
    for (int i = 1000; i > 0; i--) {
        set->add(i);
    }
    int count = 0;
    int* a = set->toArray(count);
    for (int i = 0; i < 10; i++) {
        REQUIRE(i + 1 == a[i]);
    }
    delete[] a;

    set->remove(1);
    REQUIRE(999 == set->size());

    set->clear();
    REQUIRE(0 == set->size());

    delete set;
}
