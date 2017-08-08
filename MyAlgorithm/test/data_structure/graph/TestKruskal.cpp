#include "catch.hpp"
#include "data_structure/graph/MstKruskal.h"

TEST_CASE("Kruskal", "[Kruskal]") {
    // 1->2 1->3 2->3 3->4 1->4
    KruskalGraph g(7);  // 4 nodes
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

    set<pair<int, int>> expected{{1, 6}, {5, 4}, {1, 2}, {5, 6}, {0, 5}, {4, 3}};
    set<pair<int, int>> edges;
    vector<KruskalEdge> selected = g.Kruskal();

    for (vector<KruskalEdge>::iterator it = selected.begin(); it < selected.end(); it++) {
        edges.insert({it->x, it->y});
    }
    REQUIRE(expected == edges);
    cout << endl;
}
