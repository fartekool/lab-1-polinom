#include "gtest.h"
#include "../polynomial_algebra/PostfixCalculator.h"
#include "../polynomial_algebra/PostfixCalculator.cpp"

TEST(PostfixCalculator, can_calculate_simple_addition) {
    std::vector<Token> tokens = {
        Token("p1", Token::Type::POLINOM_NAME, Token::OperatorAssociativity::NONE),
        Token("p2", Token::Type::POLINOM_NAME, Token::OperatorAssociativity::NONE),
        Token("+", Token::Type::OPERATOR, Token::OperatorAssociativity::LEFT)
    };
    std::map<std::string, Polynom> pol = {
        {"p1", Polynom("x + 1")},
        {"p2", Polynom("y + 2")}
    };
    Polynom result = PostfixCalculator::Calculate(tokens, pol);
    ASSERT_EQ(result.GetInfix(), "x + y + 3");
}

TEST(PostfixCalculator, can_calculate_simple_subtraction) {
    std::vector<Token> tokens = {
        Token("p1", Token::Type::POLINOM_NAME, Token::OperatorAssociativity::NONE),
        Token("p2", Token::Type::POLINOM_NAME, Token::OperatorAssociativity::NONE),
        Token("-", Token::Type::OPERATOR, Token::OperatorAssociativity::LEFT)
    };
    std::map<std::string, Polynom> pol = {
        {"p1", Polynom("x + 1")},
        {"p2", Polynom("y + 2")}
    };
    Polynom result = PostfixCalculator::Calculate(tokens, pol);
    ASSERT_EQ(result.GetInfix(), "x - y - 1");
}


TEST(PostfixCalculator, can_calculate_simple_multiplication) {
    std::vector<Token> tokens = {
        Token("p1", Token::Type::POLINOM_NAME, Token::OperatorAssociativity::NONE),
        Token("p2", Token::Type::POLINOM_NAME, Token::OperatorAssociativity::NONE),
        Token("*", Token::Type::OPERATOR, Token::OperatorAssociativity::LEFT)
    };
    std::map<std::string, Polynom> pol = {
        {"p1", Polynom("x + 1")},
        {"p2", Polynom("y + 2")}
    };
    Polynom result = PostfixCalculator::Calculate(tokens, pol);
    ASSERT_EQ(result.GetInfix(), "xy + 2x + y + 2");
}

TEST(PostfixCalculator, can_calculate_unary_minus) {
    std::vector<Token> tokens = {
        Token("p1", Token::Type::POLINOM_NAME, Token::OperatorAssociativity::NONE),
        Token("-", Token::Type::OPERATOR, Token::OperatorAssociativity::RIGHT)
    };
    std::map<std::string, Polynom> pol = {
        {"p1", Polynom("x + 1")}
    };
    Polynom result = PostfixCalculator::Calculate(tokens, pol);
    ASSERT_EQ(result.GetInfix(), "-x - 1");
}

TEST(PostfixCalculator, can_calculate_complex_expression) {
    std::vector<Token> tokens = {
        Token("p1", Token::Type::POLINOM_NAME, Token::OperatorAssociativity::NONE),
        Token("p2", Token::Type::POLINOM_NAME, Token::OperatorAssociativity::NONE),
        Token("+", Token::Type::OPERATOR, Token::OperatorAssociativity::LEFT),
        Token("p3", Token::Type::POLINOM_NAME, Token::OperatorAssociativity::NONE),
        Token("*", Token::Type::OPERATOR, Token::OperatorAssociativity::LEFT)
    };
    std::map<std::string, Polynom> pol = {
        {"p1", Polynom("x")},
        {"p2", Polynom("y")},
        {"p3", Polynom("z")}
    };
    Polynom result = PostfixCalculator::Calculate(tokens, pol);
    ASSERT_EQ(result.GetInfix(), "xz + yz");
}

TEST(PostfixCalculator, can_calculate_integer_literal) {
    std::vector<Token> tokens = {
        Token("10", Token::Type::INT_LITERAL, Token::OperatorAssociativity::NONE)
    };
    std::map<std::string, Polynom> pol = {};
    Polynom result = PostfixCalculator::Calculate(tokens, pol);
    ASSERT_EQ(result.GetInfix(), "10");
}

TEST(PostfixCalculator, can_calculate_float_literal) {
    std::vector<Token> tokens = {
        Token("3.14", Token::Type::FLOAT_LITERAL, Token::OperatorAssociativity::NONE)
    };
    std::map<std::string, Polynom> pol = {};
    Polynom result = PostfixCalculator::Calculate(tokens, pol);
    ASSERT_EQ(result.GetInfix(), "3.14");
}

TEST(PostfixCalculator, throws_on_unknown_operator) {
    std::vector<Token> tokens = {
        Token("p1", Token::Type::POLINOM_NAME, Token::OperatorAssociativity::NONE),
        Token("p2", Token::Type::POLINOM_NAME, Token::OperatorAssociativity::NONE),
        Token("/", Token::Type::OPERATOR, Token::OperatorAssociativity::LEFT)
    };
    std::map<std::string, Polynom> pol = {
        {"p1", Polynom("x")},
        {"p2", Polynom("y")}
    };
    ASSERT_THROW(PostfixCalculator::Calculate(tokens, pol), std::runtime_error);
}

TEST(PostfixCalculator, throws_on_polynom_not_found) {
    std::vector<Token> tokens = {
        Token("p1", Token::Type::POLINOM_NAME, Token::OperatorAssociativity::NONE)
    };
    std::map<std::string, Polynom> pol = {};
    ASSERT_THROW(PostfixCalculator::Calculate(tokens, pol), std::runtime_error);
}

TEST(PostfixCalculator, throws_on_unexpected_token_type) {
    std::vector<Token> tokens = {
        Token("p1", static_cast<Token::Type>(100), Token::OperatorAssociativity::NONE) 
    };
    std::map<std::string, Polynom> pol = {};
    ASSERT_THROW(PostfixCalculator::Calculate(tokens, pol), std::runtime_error);
}