#include "catch.hpp"
#include "data_structure/graph/DenseGraph.h"

TEST_CASE("DenseGraph Max Flow", "[Edmonds_Karp]") {
    DenseGraph g(6);
    // example from 算法导论 P405
    g.setEdge(0, 1, 16);
    g.setEdge(0, 2, 13);
    g.setEdge(1, 2, 10);
    g.setEdge(1, 3, 12);
    g.setEdge(2, 1, 4);
    g.setEdge(2, 4, 14);
    g.setEdge(3, 2, 9);
    g.setEdge(3, 5, 20);
    g.setEdge(4, 3, 7);
    g.setEdge(4, 5, 4);

    REQUIRE(23 == g.Edmonds_Karp(0, 5));
}

TEST_CASE("DenseGraph Dijkstra", "[Dijkstra]") {
    DenseGraph g(5);  // 5 nodes
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
    REQUIRE(9 == g.dist[root][target]);                                // distance from root to target
    REQUIRE(vector<int>({0, 3, 1, 2}) == g.trajectory(root, target));  // route from root to target
}

TEST_CASE("DenseGraph FloydWarshall", "[FloydWarshall]") {
    DenseGraph g(5);  // 5 nodes
    // 算法导论P384图25-1 算法结果在P388
    g.setEdge(0, 1, 3);
    g.setEdge(0, 2, 8);
    g.setEdge(0, 4, -4);
    g.setEdge(1, 3, 1);
    g.setEdge(1, 4, 7);
    g.setEdge(2, 1, 4);
    g.setEdge(3, 0, 2);
    g.setEdge(3, 2, -5);
    g.setEdge(4, 3, 6);

    g.FloydWarshall();                                      //计算所有点对之间的最短路径
    REQUIRE(vector<int>({3, 0, 4}) == g.trajectory(3, 4));  // route from 3 to 4
    REQUIRE(vector<int>({4, 3, 2}) == g.trajectory(4, 2));  // route from 4 to 2
}
