#include "catch.hpp"
#include "math/PostfixExpression.h"

TEST_CASE("PostfixExpression", "[PostfixExpression]") {
    PostfixExpression pe;
    REQUIRE(pe.transform("A*(B+C)*D") == "ABC+*D*");
    REQUIRE(pe.transform("A/B-C+D*E-A*C") == "AB/C-DE*+AC*-");
    REQUIRE(pe.transform("((((A/B)-C)+(D*E))-(A*C))") == "AB/C-DE*+AC*-");
}
