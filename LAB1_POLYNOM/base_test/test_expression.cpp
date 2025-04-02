#include "gtest.h"
#include "../polynomial_algebra/Expression.h"
#include "../polynomial_algebra/Expression.cpp"

TEST(Expression, can_get_infix) {
    Expression expr("p1 + p2 * p3");
    ASSERT_EQ(expr.GetInfix(), "p1 + p2 * p3");
}

TEST(Expression, can_get_postfix) {
    Expression expr("p1 + p2 * p3");
    ASSERT_EQ(expr.GetPostfix(), "p1 p2 p3 * + ");
}

TEST(Expression, can_get_operands) {
    Expression expr("p1 + p2 * p3");
    std::vector<std::string> expected = { "p1", "p2", "p3" };
    ASSERT_EQ(expr.GetOperands(), expected);
}

TEST(Expression, can_calculate_simple_expression) {
    Expression expr("p1 + p2");
    std::map<std::string, Polynom> pol = {
        {"p1", Polynom("x + 1")},
        {"p2", Polynom("y + 2")}
    };
    Polynom result = expr.Calculate(pol);
    ASSERT_EQ(result.GetInfix(), "x + y + 3");
}

TEST(Expression, can_calculate_complex_expression) {
    Expression expr("p1 + p2 * p3");
    std::map<std::string, Polynom> pol = {
        {"p1", Polynom("x")},
        {"p2", Polynom("y")},
        {"p3", Polynom("z")}
    };
    Polynom result = expr.Calculate(pol);
    ASSERT_EQ(result.GetInfix(), "x + yz");
}

TEST(Expression, can_calculate_expression_with_unary_minus) {
    Expression expr("-p1 + p2");
    std::map<std::string, Polynom> pol = {
        {"p1", Polynom("x")},
        {"p2", Polynom("y")}
    };
    Polynom result = expr.Calculate(pol);
    ASSERT_EQ(result.GetInfix(), "-x + y");
}

TEST(Expression, throws_on_invalid_expression) {
    ASSERT_THROW(Expression("p1 ++ p2"), std::invalid_argument);
}

TEST(Expression, throws_on_missing_polynom) {
    Expression expr("p1 + p2");
    std::map<std::string, Polynom> pol = {
        {"p1", Polynom("x")}
    };
    ASSERT_THROW(expr.Calculate(pol), std::runtime_error);
}

TEST(Expression, can_calculate_with_literals) {
    Expression expr("10 + p1 * 3.14");
    std::map<std::string, Polynom> pol = {
        {"p1", Polynom("x")}
    };
    Polynom result = expr.Calculate(pol);
    ASSERT_EQ(result.GetInfix(), "3.14x + 10");
}