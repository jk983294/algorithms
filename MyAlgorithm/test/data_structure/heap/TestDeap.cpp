#include "catch.hpp"
#include "data_structure/heap/Deap.h"

TEST_CASE("Deap", "[Deap]") {
    int ret;
    Deap<int> h;
    h.insertKey(2);
    h.insertKey(3);
    h.insertKey(7);
    h.insertKey(5);
    h.insertKey(6);
    h.insertKey(9);
    REQUIRE(vector<int>({2, 9, 3, 5, 6, 7}) == vector<int>(h.heap.begin() + 2, h.heap.begin() + h.size + 2));

    h.deleteMax(ret);
    REQUIRE(vector<int>({2, 7, 3, 5, 6}) == vector<int>(h.heap.begin() + 2, h.heap.begin() + h.size + 2));
    h.deleteMax(ret);
    REQUIRE(vector<int>({2, 6, 3, 5}) == vector<int>(h.heap.begin() + 2, h.heap.begin() + h.size + 2));
    h.deleteMax(ret);
    REQUIRE(vector<int>({2, 5, 3}) == vector<int>(h.heap.begin() + 2, h.heap.begin() + h.size + 2));
    h.deleteMax(ret);
    REQUIRE(vector<int>({2, 3}) == vector<int>(h.heap.begin() + 2, h.heap.begin() + h.size + 2));
    h.deleteMax(ret);
    REQUIRE(vector<int>({2}) == vector<int>(h.heap.begin() + 2, h.heap.begin() + h.size + 2));
    h.deleteMax(ret);
    REQUIRE(vector<int>() == vector<int>(h.heap.begin() + 2, h.heap.begin() + h.size + 2));
    h.deleteMax(ret);
    REQUIRE(vector<int>() == vector<int>(h.heap.begin() + 2, h.heap.begin() + h.size + 2));
}
