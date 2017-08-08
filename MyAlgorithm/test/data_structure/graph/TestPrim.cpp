#include "catch.hpp"
#include "data_structure/graph/MstPrim.h"

TEST_CASE("Prim", "[Prim]") {
    // 1->2 1->3 2->3 3->4 1->4
    MstPrim g(7);  // 4 nodes
    // 10 edge  (v,w)
    g.setEdge(0, 5, 10);
    g.setEdge(0, 1, 22);
    g.setEdge(1, 2, 6);
    g.setEdge(1, 6, 2);
    g.setEdge(5, 6, 7);
    g.setEdge(5, 4, 3);
    g.setEdge(6, 2, 9);
    g.setEdge(6, 4, 11);
    g.setEdge(4, 3, 12);
    g.setEdge(2, 3, 23);

    set<pair<int, int>> expected{{0, 5}, {1, 2}, {4, 3}, {5, 4}, {5, 6}, {6, 1}};
    set<pair<int, int>> edges = g.prim();

    REQUIRE(expected == edges);
}
