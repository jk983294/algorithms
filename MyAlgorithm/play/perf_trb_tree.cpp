
#include <set>
#include <unordered_set>
#include "data_structure/tree/threaded_rbtree.h"
#include "data_structure/tree/threaded_rbtree_hash.h"

#include <chrono>
#include <cstring>
#include <iostream>
#include <map>
#include <random>
#include <string>
#include <unordered_map>

template <typename T>
void test_set_insert(T& container, const std::vector<int>& v_arr, const std::string& desc) {
    auto start = std::chrono::system_clock::now();
    for (auto& value : v_arr) {
        container.insert(value);
    }
    auto elapse = std::chrono::nanoseconds{std::chrono::system_clock::now() - start}.count();
    printf("%zu %s insert elapse %zu ns\n", container.size(), desc.c_str(), elapse);
}

template <typename T>
void test_map_insert(T& container, const std::vector<int>& v_arr, const std::string& desc) {
    auto start = std::chrono::system_clock::now();
    for (auto& value : v_arr) {
        container.emplace(value, value);
    }
    auto elapse = std::chrono::nanoseconds{std::chrono::system_clock::now() - start}.count();
    printf("%zu %s insert elapse %zu ns\n", container.size(), desc.c_str(), elapse);
}

template <typename T>
void test_find(T& container, const std::vector<int>& v_arr, const std::string& desc, int offset = 0) {
    int cnt = 0, miss = 0;
    auto start = std::chrono::system_clock::now();
    for (auto& value : v_arr) {
        auto itr = container.find(value + offset);
        if (itr == container.end()) {
            miss++;
        } else {
            cnt++;
        }
    }
    auto elapse = std::chrono::nanoseconds{std::chrono::system_clock::now() - start}.count();
    printf("%zu %s find elapse %zu (%d,%d)\n", container.size(), desc.c_str(), elapse, cnt, miss);
}

template <typename T>
void test_erase(T& container, const std::vector<int>& v_arr, const std::string& desc, int offset = 0) {
    auto start = std::chrono::system_clock::now();
    for (auto& value : v_arr) {
        container.erase(value + offset);
    }
    auto elapse = std::chrono::nanoseconds{std::chrono::system_clock::now() - start}.count();
    printf("%zu %s erase elapse %zu ns\n", container.size(), desc.c_str(), elapse);
}

void test(size_t size) {
    std::mt19937 mt(time(nullptr));
    auto mtr = std::uniform_int_distribution<int>(-200000000, 200000000);
    std::vector<int> v_arr;
    v_arr.resize(size);
    for (auto& value : v_arr) {
        value = mtr(mt);
    }

    trb_set<int32_t> s0;
    std::set<int32_t> s1;
    trb_map<int32_t, double> m0;
    std::map<int32_t, double> m1;

    printf("%zu start\n", size);
    test_set_insert(s0, v_arr, "trb_set");
    test_set_insert(s1, v_arr, "std::set");
    test_map_insert(m0, v_arr, "trb_map");
    test_map_insert(m1, v_arr, "std::map");

    test_find(s0, v_arr, "trb_set");
    test_find(s1, v_arr, "std::set");
    test_find(m0, v_arr, "trb_map");
    test_find(m1, v_arr, "std::map");

    test_find(s0, v_arr, "trb_set miss", 1);
    test_find(s1, v_arr, "std::set miss", 1);
    test_find(m0, v_arr, "trb_map miss", 1);
    test_find(m1, v_arr, "std::map miss", 1);

    test_erase(s0, v_arr, "trb_set miss", 1);
    test_erase(s1, v_arr, "std::set miss", 1);
    test_erase(m0, v_arr, "trb_map miss", 1);
    test_erase(m1, v_arr, "std::map miss", 1);

    test_erase(s0, v_arr, "trb_set");
    test_erase(s1, v_arr, "std::set");
    test_erase(m0, v_arr, "trb_map");
    test_erase(m1, v_arr, "std::map");
    printf("%zu end\n", size);
}

void test_hash(size_t size) {
    std::mt19937 mt(time(nullptr));
    auto mtr = std::uniform_int_distribution<int>(-200000000, 200000000);
    std::vector<int> v_arr;
    v_arr.resize(size);
    for (auto& value : v_arr) {
        value = mtr(mt);
    }

    trb_hash_set<int32_t> s0;
    std::unordered_set<int32_t> s1;
    trb_hash_map<int32_t, double> m0;
    std::unordered_map<int32_t, double> m1;

    printf("%zu start\n", size);
    test_set_insert(s0, v_arr, "trb_hash_set");
    test_set_insert(s1, v_arr, "std::unordered_set");
    test_map_insert(m0, v_arr, "trb_hash_map");
    test_map_insert(m1, v_arr, "std::unordered_map");

    test_find(s0, v_arr, "trb_hash_set");
    test_find(s1, v_arr, "std::unordered_set");
    test_find(m0, v_arr, "trb_hash_map");
    test_find(m1, v_arr, "std::unordered_map");

    test_find(s0, v_arr, "trb_hash_set miss", 1);
    test_find(s1, v_arr, "std::unordered_set miss", 1);
    test_find(m0, v_arr, "trb_hash_map miss", 1);
    test_find(m1, v_arr, "std::unordered_map miss", 1);

    test_erase(s0, v_arr, "trb_hash_set miss", 1);
    test_erase(s1, v_arr, "std::unordered_set miss", 1);
    test_erase(m0, v_arr, "trb_hash_map miss", 1);
    test_erase(m1, v_arr, "std::unordered_map miss", 1);

    test_erase(s0, v_arr, "trb_hash_set");
    test_erase(s1, v_arr, "std::unordered_set");
    test_erase(m0, v_arr, "trb_hash_map");
    test_erase(m1, v_arr, "std::unordered_map");
    printf("%zu end\n", size);
}

int main() {
    test(100);
    test(1000);
    test(10000);
    test(100000);
    test(1000000);
    // test(10000000);

    test_hash(100);
    test_hash(1000);
    test_hash(10000);
    test_hash(100000);
    test_hash(1000000);
    // test(10000000);
}
