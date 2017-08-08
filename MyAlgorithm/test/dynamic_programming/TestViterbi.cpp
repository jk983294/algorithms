#include "catch.hpp"
#include "dynamic_programming/Viterbi.h"

TEST_CASE("Viterbi", "[Viterbi]") {
    Viterbi v("/var/tmp/test/ViterbiConf.txt");
    //    v.print();
    v.calculate();
    //    v.print();
    REQUIRE(vector<int>({0, 1, 0, 0}) == v.path);
}
