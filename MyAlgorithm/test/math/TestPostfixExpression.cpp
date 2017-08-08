#include "catch.hpp"
#include "math/PostfixExpression.h"

TEST_CASE("PostfixExpression", "[PostfixExpression]") {
    REQUIRE(transform_to_postfix_expression("A*(B+C)*D") == "ABC+*D*");
    REQUIRE(transform_to_postfix_expression("A/B-C+D*E-A*C") == "AB/C-DE*+AC*-");
    REQUIRE(transform_to_postfix_expression("((((A/B)-C)+(D*E))-(A*C))") == "AB/C-DE*+AC*-");
}
