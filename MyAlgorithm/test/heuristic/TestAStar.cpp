#include "catch.hpp"
#include "heuristic/AStar.h"

TEST_CASE("AStar", "[AStar]") {
    position start(3, 2);
    position end(3, 5);
    AStar a("/var/tmp/test/AStarMap.txt");

    vector<pair<int, int>> expectedPath1{{3, 5}, {2, 4}, {1, 3}, {2, 2}, {3, 2}};
    vector<pair<int, int>> path1 = a.findPath(start, end);
    REQUIRE(expectedPath1 == path1);
}

TEST_CASE("AStar1", "[AStar]") {
    position start(4, 1);
    position start1(7, 1);
    position start2(4, 3);
    position end(4, 6);
    AStar a("/var/tmp/test/AStarMap1.txt");

    vector<pair<int, int>> expectedPath1{{4, 6}, {5, 6}, {6, 5}, {7, 4}, {7, 3}, {6, 2}, {5, 2}, {4, 1}};
    vector<pair<int, int>> path1 = a.findPath(start, end);
    REQUIRE(expectedPath1 == path1);

    vector<pair<int, int>> expectedPath2{{4, 6}, {5, 6}, {6, 5}, {7, 4}, {7, 3}, {7, 2}, {7, 1}};
    vector<pair<int, int>> path2 = a.findPath(start1, end);
    REQUIRE(expectedPath2 == path2);

    vector<pair<int, int>> expectedPath3{{4, 6}, {3, 6}, {2, 5}, {1, 4}, {1, 3}, {2, 2}, {3, 3}, {4, 3}};
    vector<pair<int, int>> path3 = a.findPath(start2, end);
    REQUIRE(expectedPath3 == path3);
}
