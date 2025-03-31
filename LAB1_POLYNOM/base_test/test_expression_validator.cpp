#include "gtest.h"
#include "../polynomial_algebra/ExpressionValidator.h"
#include "../polynomial_algebra/ExpressionValidator.cpp"

// Тесты для ExpressionValidator::IsOperator
TEST(ExpressionValidator, IsOperator_returns_true_for_valid_operators) {
    ASSERT_TRUE(ExpressionValidator::IsOperator('+'));
    ASSERT_TRUE(ExpressionValidator::IsOperator('-'));
    ASSERT_TRUE(ExpressionValidator::IsOperator('*'));
}

TEST(ExpressionValidator, IsOperator_returns_false_for_invalid_characters) {
    ASSERT_FALSE(ExpressionValidator::IsOperator('a'));
    ASSERT_FALSE(ExpressionValidator::IsOperator('1'));
    ASSERT_FALSE(ExpressionValidator::IsOperator('('));
    ASSERT_FALSE(ExpressionValidator::IsOperator(')'));
    ASSERT_FALSE(ExpressionValidator::IsOperator(' '));
    ASSERT_FALSE(ExpressionValidator::IsOperator('.'));
    ASSERT_FALSE(ExpressionValidator::IsOperator('_'));
}

// Тесты для ExpressionValidator::Validate
TEST(ExpressionValidator, Validate_does_not_throw_for_valid_expression) {
    ASSERT_NO_THROW(ExpressionValidator::Validate("1 + 2 * (a_var - 3.5)"));
}

TEST(ExpressionValidator, Validate_throws_for_invalid_characters) {
    ASSERT_THROW(ExpressionValidator::Validate("1 + 2 @ 3"), std::invalid_argument);
}

TEST(ExpressionValidator, Validate_throws_for_unbalanced_parentheses) {
    ASSERT_THROW(ExpressionValidator::Validate("(1 + 2) * 3)"), std::invalid_argument);
    ASSERT_THROW(ExpressionValidator::Validate("(1+1"), std::invalid_argument);
}