#include "catch.hpp"
#include "data_structure/graph/SparseGraph.h"

TEST_CASE("SparseGraph Dijkstra", "[Dijkstra]") {
    SparseGraph g(5);  // 5 nodes
    // example from 算法导论 P367
    g.setEdge(0, 1, 10);
    g.setEdge(0, 3, 5);
    g.setEdge(1, 2, 1);
    g.setEdge(1, 3, 2);
    g.setEdge(2, 4, 4);
    g.setEdge(3, 1, 3);
    g.setEdge(3, 2, 9);
    g.setEdge(3, 4, 2);
    g.setEdge(4, 0, 7);
    g.setEdge(4, 2, 6);

    int root = 0, target = 2;
    g.Dijkstra(root);
    REQUIRE(vector<int>({0, 3, 1, 2}) == g.trajectory(root, target));  // route from root to target

    g.DFS_non_recursive(0);
    REQUIRE(vector<int>({0, 1, 2, 4, 3}) == g.traverseResult);
    g.DFS_recursive(0);
    REQUIRE(vector<int>({0, 3, 4, 2, 1}) == g.traverseResult);
    g.BFS(0);
    REQUIRE(vector<int>({0, 3, 1, 4, 2}) == g.traverseResult);
}

TEST_CASE("SparseGraph SPFA", "[SPFA]") {
    SparseGraph g(5);  // 5 nodes
    //例子来自算法导论 362
    g.setEdge(0, 1, 6);
    g.setEdge(0, 3, 7);
    g.setEdge(1, 2, 5);
    g.setEdge(1, 3, 8);  // 无负环
    g.setEdge(1, 4, -4);
    g.setEdge(2, 1, -2);
    g.setEdge(3, 2, -3);
    g.setEdge(3, 4, 9);
    g.setEdge(4, 0, 2);
    g.setEdge(4, 2, 7);

    REQUIRE(g.SPFA(0));
    REQUIRE(vector<int>({0, 3, 2, 1, 4}) == g.trajectory(0, 4));  // route from start to 4
    REQUIRE(g.BellmanFord(0));
    REQUIRE(vector<int>({0, 3, 2, 1, 4}) == g.trajectory(0, 4));  // route from start to 4
}

TEST_CASE("SparseGraph SPFA negative loop", "[SPFA negative loop]") {
    SparseGraph g(5);  // 5 nodes
    //例子来自算法导论 362
    g.setEdge(0, 1, 6);
    g.setEdge(0, 3, 7);
    g.setEdge(1, 2, 5);
    g.setEdge(1, 3, 4);  // 有负环
    g.setEdge(1, 4, -4);
    g.setEdge(2, 1, -2);
    g.setEdge(3, 2, -3);
    g.setEdge(3, 4, 9);
    g.setEdge(4, 0, 2);
    g.setEdge(4, 2, 7);

    REQUIRE(!g.SPFA(0));
    REQUIRE(!g.BellmanFord(0));
}
