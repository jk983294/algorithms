#include "catch.hpp"
#include "data_structure/HashTable.h"

TEST_CASE("HashTable", "[HashTable]") {
    // MAX_N个数据 MAX_QUERY次查询
    const int MAX_N = 500;

    vector<int> a(MAX_N);

    const int MAX_NUM = MAX_N * 4;

    // 随机生成在[0, MAX_NUM)范围内的MAX_N个数
    int i;
    srand((unsigned int)time(NULL));
    for (i = 0; i < MAX_N; ++i) a[i] = (rand() * rand()) % MAX_NUM;

    hash_table<int> myHashTable(6291469);

    // insert
    for (i = 0; i < MAX_N; i++) myHashTable.insert(a[i]);

    // find
    for (i = 0; i < MAX_N; ++i) REQUIRE(myHashTable.find(a[i]));
}
