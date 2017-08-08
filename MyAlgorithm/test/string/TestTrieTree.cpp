#include "catch.hpp"
#include "string/TrieTree.h"

TEST_CASE("TrieTree", "[TrieTree]") {
    Trie trie;
    trie.insert("zbdfasd");
    trie.insert("zbcfd");
    trie.insert("zbcdfdasfasf");
    trie.insert("abcdaf");
    trie.insert("defdasfa");
    trie.insert("fedfasfd");
    trie.insert("dfdfsa");
    trie.insert("dadfd");
    trie.insert("dfdfasf");
    trie.insert("abcfdfa");
    trie.insert("fbcdfd");
    trie.insert("abcdaf");
    trie.sort();

    vector<pair<string, int>> expected{{"abcdaf", 2},       {"abcfdfa", 1}, {"dadfd", 1},  {"defdasfa", 1},
                                       {"dfdfasf", 1},      {"dfdfsa", 1},  {"fbcdfd", 1}, {"fedfasfd", 1},
                                       {"zbcdfdasfasf", 1}, {"zbcfd", 1},   {"zbdfasd", 1}};
    REQUIRE(expected == trie.result);
}
