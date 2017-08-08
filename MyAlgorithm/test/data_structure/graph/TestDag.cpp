#include "catch.hpp"
#include "data_structure/graph/DAG.h"

TEST_CASE("DAG", "[DAG]") {
    DAG g(6);  // 5 nodes
    //例子来自算法导论 365
    g.setEdge(0, 1, 5);
    g.setEdge(0, 2, 3);
    g.setEdge(1, 2, 2);
    g.setEdge(1, 3, 6);
    g.setEdge(2, 3, 7);
    g.setEdge(2, 4, 4);
    g.setEdge(2, 5, 2);
    g.setEdge(3, 4, -1);
    g.setEdge(3, 5, 1);
    g.setEdge(4, 5, -2);

    REQUIRE(g.shortestPath(0));
    REQUIRE(vector<int>({0, 1, 2, 3, 4, 5}) == g.topoSortResult);
    REQUIRE(vector<int>({0, 5, 3, 10, 7, 5}) == vector<int>(g.dist, g.dist + g.n));
    REQUIRE(vector<int>({-1, 0, 0, 2, 2, 2}) == vector<int>(g.path, g.path + g.n));

    REQUIRE(g.shortestPath(2));
    REQUIRE(vector<int>({0, 1, 2, 3, 4, 5}) == g.topoSortResult);
    REQUIRE(vector<int>({10000000, 10000000, 0, 7, 4, 2}) == vector<int>(g.dist, g.dist + g.n));
    REQUIRE(vector<int>({-1, -1, -1, 2, 2, 2}) == vector<int>(g.path, g.path + g.n));

    g.setEdge(5, 0, 1);  //加了一条回边，测试拓扑排序
    REQUIRE(!g.shortestPath(0));
}
